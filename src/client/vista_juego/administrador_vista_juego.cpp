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

void AdministradorVistaJuego::actualizar_vista() {
    std::shared_ptr<SnapshotDTO> snapshot;
    if (!cliente.obtener_snapshot(snapshot)) {
        if (!primera_snapshot_recibida) {
            pantalla_carga.dibujar();
        }
        return;
    }

    primera_snapshot_recibida = true;

    if (snapshot->es_fin_juego()) {
        fin_juego = true;
        return;
    }

    if (!fondo_escenario) {
        tipo_escenario = snapshot->obtener_tipo_escenario();
        SDL2pp::Texture& textura_fondo = lector_texturas.obtener_textura_fondo_escenario(
                MAPA_TIPO_ESCENARIO.at(tipo_escenario));
        const SDL2pp::Rect& coords_fondo = lector_texturas.obtener_coords_fondo_escenario(
                MAPA_TIPO_ESCENARIO.at(tipo_escenario));
        fondo_escenario.emplace(ANCHO_VENTANA, ALTO_VENTANA, renderer, textura_fondo, coords_fondo);
    }

    const std::vector<ClienteDTO> clientes_recibidos = snapshot->obtener_clientes();

    // Actualizar posición de la cámara
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
        /*hud.actualizar(jugador->puntos, jugador->vida, jugador->arma_actual,
                       jugador->balas_restantes);*/
    }

    if (const std::vector<BloqueEscenarioDTO> bloques_recibidos =
                snapshot->obtener_bloques_escenario();
        !bloques_recibidos.empty()) {
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

    std::unordered_set<uint32_t> ids_clientes_recibidos;
    for (auto c: clientes_recibidos) {
        ids_clientes_recibidos.insert(c.id_cliente);
        if (personajes.count(c.id_cliente) == 0) {
            Personaje nuevo_personaje(c.id_cliente, MAPA_TIPO_PERSONAJE.at(c.tipo_personaje),
                                      renderer, lector_texturas, camara, c.pos_x, c.pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(c.id_cliente, std::move(nuevo_personaje));
        }

        personajes.at(c.id_cliente)
                .actualizar_animacion(MAPA_ESTADOS_PERSONAJE.at(c.estado), iteraciones_actuales,
                                      {c.pos_x, c.pos_y, 2, 2}, 0, c.de_espaldas);
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

int64_t AdministradorVistaJuego::sincronizar_vista(const int64_t ticks_transcurridos) {
    int64_t ajuste_tiempo_anterior = 0;
    int64_t tiempo_rest = MILISEGUNDOS_POR_FRAME - ticks_transcurridos;
    if (tiempo_rest < 0) {
        const int64_t tiempo_atrasado = -tiempo_rest;
        tiempo_rest = MILISEGUNDOS_POR_FRAME - tiempo_atrasado % MILISEGUNDOS_POR_FRAME;
        ajuste_tiempo_anterior += tiempo_rest + tiempo_atrasado;
        iteraciones_actuales += ajuste_tiempo_anterior / MILISEGUNDOS_POR_FRAME;

        // Debemos droppear frames de animación, algunas snapshots se pierden
        for (int i = 0; i < tiempo_atrasado / MILISEGUNDOS_POR_FRAME; i++) {
            if (std::shared_ptr<SnapshotDTO> snapshot; !cliente.obtener_snapshot(snapshot)) {
                break;
            }
        }
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
        // hud(renderer, lector_texturas),
        cliente(cliente),
        iteraciones_actuales(0),
        tipo_escenario(ESCENARIO_INDEFINIDO),
        primera_snapshot_recibida(false),
        fin_juego(false) {
    lector_texturas.cargar_texturas_y_coordenadas();
}

void AdministradorVistaJuego::run() {
    int64_t ticks_anteriores = 0;
    while (!fin_juego) {
        actualizar_vista();
        renderer.Clear();
        if (fondo_escenario) {
            fondo_escenario->dibujar();
        }
        for (auto& [fst, snd]: bloques_escenario) {
            snd->dibujar();
        }
        for (auto& [fst, snd]: personajes) {
            snd.dibujar();
        }
        // hud.dibujar();
        renderer.Present();

        if (!entrada_juego.procesar_entrada()) {
            fin_juego = true;
        }

        const int64_t ticks_actuales = SDL_GetTicks();
        ticks_anteriores += sincronizar_vista(ticks_actuales - ticks_anteriores);
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
