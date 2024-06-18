#include "administrador_vista_juego.h"

#include <unordered_set>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../../common/snapshot_dto.h"
#include "../../common/tipo_bloque_escenario.h"

const std::unordered_map<TipoEscenario, std::string> AdministradorVistaJuego::MAPA_TIPO_ESCENARIO{
        {ESCENARIO1, "castle"},
        {ESCENARIO2, "carrotus"},
};

const std::unordered_map<TipoBloqueEscenario, std::string>
        AdministradorVistaJuego::MAPA_TIPO_BLOQUE{
                {PARED, "pared"},
                {PISO, "piso"},
                {DIAGONAL, "diagonal"},
                {DIAGONAL_INVERTIDO, "diagonal_invertido"},
                {SOPORTE_DIAGONAL, "soporte_diagonal"},
                {SOPORTE_DIAGONAL_INVERTIDO, "soporte_diagonal_invertido"},
        };

const std::unordered_map<TipoPersonaje, std::string> AdministradorVistaJuego::MAPA_TIPO_PERSONAJE{
        {JAZZ, "jazz"},
        {SPAZ, "spaz"},
        {LORI, "lori"},
};

const std::unordered_map<EstadoPersonaje, EstadoVisualPersonaje>
        AdministradorVistaJuego::MAPA_ESTADOS_PERSONAJE{{IDLE, ESTADO_STAND},
                                                        {CORRER, ESTADO_CORRER},
                                                        {DASH, ESTADO_DASH},
                                                        {DISPARAR_QUIETO, ESTADO_DISPARAR},
                                                        {SALTAR_ARRIBA, ESTADO_SALTAR_ARRIBA},
                                                        {SALTAR_ADELANTE, ESTADO_SALTAR_ADELANTE},
                                                        {CAER_ABAJO, ESTADO_CAER_ABAJO},
                                                        {CAER_ADELANTE, ESTADO_CAER_ADELANTE},
                                                        {ATAQUE_ESPECIAL, ESTADO_ATAQUE_ESPECIAL},
                                                        {INTOXICADO, ESTADO_INTOXICADO_IDLE},
                                                        {IMPACTADO, ESTADO_DANIO},
                                                        {MUERTE, ESTADO_MUERTE}};

void AdministradorVistaJuego::actualizar_vista_fondo_escenario(TipoEscenario tipo_escenario) {
    if (!fondo_escenario) {
        this->tipo_escenario = tipo_escenario;
        SDL2pp::Texture& textura_fondo = lector_texturas.obtener_textura_fondo_escenario(
                MAPA_TIPO_ESCENARIO.at(tipo_escenario));
        const SDL2pp::Rect& coords_fondo = lector_texturas.obtener_coords_fondo_escenario(
                MAPA_TIPO_ESCENARIO.at(tipo_escenario));
        fondo_escenario.emplace(ANCHO_VENTANA, ALTO_VENTANA, renderer, textura_fondo, coords_fondo);
    }
}

void AdministradorVistaJuego::actualizar_vista_camara_y_hud(
        const std::vector<ClienteDTO>& clientes_recibidos) {
    if (const auto jugador = std::find_if(
                clientes_recibidos.begin(), clientes_recibidos.end(),
                [this](const auto& cliente) { return cliente.id_cliente == this->id_jugador; });
        jugador != clientes_recibidos.end()) {
        if (personajes.count(jugador->id_cliente) == 0) {
            Personaje nuevo_personaje(jugador->id_cliente,
                                      MAPA_TIPO_PERSONAJE.at(jugador->tipo_personaje), renderer,
                                      lector_texturas, camara, jugador->pos_x, jugador->pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(jugador->id_cliente, std::move(nuevo_personaje));
        }
        personajes.at(jugador->id_cliente).actualizar_camara();

        // Actualizar HUD en base a los datos del jugador
        hud.actualizar(jugador->tipo_personaje, jugador->puntos, jugador->vida,
                       jugador->arma_actual, jugador->balas_restantes);
    }
}

void AdministradorVistaJuego::actualizar_vista_bloques_escenario(
        const std::vector<BloqueEscenarioDTO>& bloques_recibidos) {
    if (!bloques_recibidos.empty()) {
        for (auto bloque: bloques_recibidos) {
            SDL2pp::Texture& textura_bloque =
                    lector_texturas.obtener_textura_bloque(MAPA_TIPO_ESCENARIO.at(tipo_escenario));
            const SDL2pp::Rect& coords_textura = lector_texturas.obtener_coords_bloque(
                    MAPA_TIPO_ESCENARIO.at(tipo_escenario), MAPA_TIPO_BLOQUE.at(bloque.tipo));

            bloques_escenario.emplace(
                    proximo_id,
                    std::make_unique<BloqueEscenario>(
                            SDL2pp::Rect(bloque.pos_x, bloque.pos_y, static_cast<int>(bloque.ancho),
                                         static_cast<int>(bloque.alto)),
                            renderer, textura_bloque, coords_textura, camara));
            proximo_id++;
        }
    }

    for (auto& [fst, snd]: bloques_escenario) {
        snd->actualizar_vista();
    }
}

void AdministradorVistaJuego::actualizar_vista_personajes(
        const std::vector<ClienteDTO>& clientes_recibidos) {
    std::unordered_set<uint32_t> ids_clientes_recibidos;
    for (auto c: clientes_recibidos) {
        ids_clientes_recibidos.insert(c.id_cliente);
        auto id = c.id_cliente;
        if (personajes.count(c.id_cliente) == 0) {
            Personaje nuevo_personaje(c.id_cliente, MAPA_TIPO_PERSONAJE.at(c.tipo_personaje),
                                      renderer, lector_texturas, camara, c.pos_x, c.pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(id, std::move(nuevo_personaje));
        }

        personajes.at(id).actualizar_animacion(MAPA_ESTADOS_PERSONAJE.at(c.estado),
                                               iteraciones_actuales, {c.pos_x, c.pos_y, 1, 1}, 0,
                                               c.de_espaldas);
    }

    std::unordered_set<uint32_t> ids_clientes_borrar;
    for (auto& [fst, snd]: personajes) {
        if (ids_clientes_recibidos.count(fst) == 0) {
            ids_clientes_borrar.insert(fst);
        }
    }

    for (auto id: ids_clientes_borrar) {
        personajes.erase(id);
    }
}

void AdministradorVistaJuego::actualizar_vista_enemigos(
        const std::vector<EnemigoDTO>& enemigos_recibidos) {
    for (const auto& enemigo: enemigos_recibidos) {
        if (!enemigos.existe_enemigo(enemigo.id)) {
            enemigos.agregar_enemigo(enemigo.id, enemigo.tipo, {enemigo.pos_x, enemigo.pos_y, 1, 1},
                                     enemigo.invertido);
        }
        enemigos.actualizar_animacion(enemigo.id, iteraciones_actuales,
                                      {enemigo.pos_x, enemigo.pos_y, enemigo.ancho, enemigo.alto},
                                      enemigo.invertido);
    }
}

void AdministradorVistaJuego::actualizar_vista_balas(const std::vector<BalaDTO>& balas_recibidas) {
    balas.eliminar_balas();
    for (const auto& bala: balas_recibidas) {
        balas.agregar_bala(bala.tipo, bala.pos_x, bala.pos_y);
    }
}

void AdministradorVistaJuego::actualizar_vista_recogibles(
        const std::vector<RecogibleDTO>& recogibles_recibidos) {
    recogibles.eliminar_recogibles();
    for (const auto& recogible: recogibles_recibidos) {
        recogibles.agregar_recogible(recogible.tipo, {recogible.pos_x, recogible.pos_y,
                                                      recogible.ancho, recogible.alto});
    }
}

void AdministradorVistaJuego::actualizar_vista() {
    std::shared_ptr<SnapshotDTO> snapshot;
    if (!cliente.obtener_snapshot(snapshot)) {
        return;
    }

    bool quedan_snapshots = true;

    // Se procesan todas las snapshots restantes, a menos que sea la primera snapshot recibida o
    // se haya llegado al fin del juego
    while (primera_snapshot_recibida && quedan_snapshots) {
        if (!cliente.obtener_snapshot(snapshot)) {
            quedan_snapshots = false;
            continue;
        }
        if (snapshot->es_fin_juego()) {
            break;
        }
    }

    primera_snapshot_recibida = true;

    if (snapshot->es_fin_juego()) {
        fin_juego = true;
        return;
    }

    const std::vector<ClienteDTO> clientes_recibidos = snapshot->obtener_clientes();

    actualizar_vista_fondo_escenario(snapshot->obtener_tipo_escenario());
    actualizar_vista_camara_y_hud(clientes_recibidos);
    actualizar_vista_bloques_escenario(snapshot->obtener_bloques_escenario());
    actualizar_vista_personajes(clientes_recibidos);
    actualizar_vista_enemigos(snapshot->obtener_enemigos());
    actualizar_vista_balas(snapshot->obtener_balas());
    actualizar_vista_recogibles(snapshot->obtener_recogibles());
}

int64_t AdministradorVistaJuego::sincronizar_vista(const int64_t ticks_transcurridos) {
    int64_t ajuste_tiempo_anterior = 0;
    int64_t tiempo_rest = MILISEGUNDOS_POR_FRAME - ticks_transcurridos;
    if (tiempo_rest < 0) {
        const int64_t tiempo_atrasado = -tiempo_rest;
        tiempo_rest = MILISEGUNDOS_POR_FRAME - tiempo_atrasado % MILISEGUNDOS_POR_FRAME;
        ajuste_tiempo_anterior += tiempo_rest + tiempo_atrasado;
        iteraciones_actuales += ajuste_tiempo_anterior / MILISEGUNDOS_POR_FRAME;
    }
    const auto tiempo_rest_final = static_cast<uint32_t>(tiempo_rest);
    SDL_Delay(tiempo_rest_final);

    ajuste_tiempo_anterior += MILISEGUNDOS_POR_FRAME;
    iteraciones_actuales++;
    return ajuste_tiempo_anterior;
}

AdministradorVistaJuego::AdministradorVistaJuego(const int32_t id_cliente,
                                                 const std::string& titulo_ventana,
                                                 Cliente& cliente):
        id_jugador(static_cast<uint32_t>(id_cliente)),
        proximo_id(0),
        sdl(SDL_INIT_VIDEO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        pantalla_carga(renderer),
        lector_texturas(renderer),
        entrada_juego(cliente),
        hud(id_cliente, renderer, lector_texturas),
        cliente(cliente),
        iteraciones_actuales(0),
        tipo_escenario(ESCENARIO_INDEFINIDO),
        enemigos(renderer, lector_texturas, camara),
        balas(renderer, lector_texturas, camara),
        recogibles(renderer, lector_texturas, camara),
        primera_snapshot_recibida(false),
        fin_juego(false) {
    lector_texturas.cargar_texturas_y_coordenadas();
}

void AdministradorVistaJuego::run() {
    int64_t ticks_anteriores = 0;
    while (!fin_juego) {
        if (!entrada_juego.procesar_entrada()) {
            fin_juego = true;
        }

        actualizar_vista();
        renderer.Clear();
        if (fondo_escenario) {
            fondo_escenario->dibujar();
        }
        for (auto& [fst, snd]: bloques_escenario) {
            snd->dibujar();
        }
        recogibles.dibujar_recogibles();
        balas.dibujar_balas();
        enemigos.dibujar_enemigos();

        for (auto& [fst, snd]: personajes) {
            snd.dibujar();
        }
        if (primera_snapshot_recibida) {
            hud.dibujar();
        } else {
            pantalla_carga.dibujar();
        }

        renderer.Present();

        const int64_t ticks_actuales = SDL_GetTicks();
        ticks_anteriores += sincronizar_vista(ticks_actuales - ticks_anteriores);
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
