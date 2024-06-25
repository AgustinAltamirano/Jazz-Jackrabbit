#include "administrador_vista_juego.h"

#include <algorithm>
#include <tuple>
#include <unordered_set>
#include <utility>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../../common/snapshot_dto.h"
#include "../../common/tipo_arma.h"
#include "../../common/tipo_bloque_escenario.h"

#include "tipo_sonido.h"
#include "vista_juego_defs.h"

const std::unordered_map<TipoEscenario, std::string> AdministradorVistaJuego::MAPA_TIPO_ESCENARIO{
        {ESCENARIO_CASTLE, "castle"},
        {ESCENARIO_CARROTUS, "carrotus"},
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
        AdministradorVistaJuego::MAPA_ESTADOS_PERSONAJE{
                {IDLE, ESTADO_STAND},
                {CORRER, ESTADO_CORRER},
                {DASH, ESTADO_DASH},
                {DISPARAR_QUIETO, ESTADO_DISPARAR},
                {SALTAR_ARRIBA, ESTADO_SALTAR_ARRIBA},
                {SALTAR_ADELANTE, ESTADO_SALTAR_ADELANTE},
                {CAER_ABAJO, ESTADO_CAER_ABAJO},
                {CAER_ADELANTE, ESTADO_CAER_ADELANTE},
                {ATAQUE_ESPECIAL, ESTADO_ATAQUE_ESPECIAL},
                {INTOXICADO, ESTADO_INTOXICADO_IDLE},
                {INTOXICADO_MOVIMIENTO, ESTADO_INTOXICADO_CAMINAR},
                {IMPACTADO, ESTADO_DANIO},
                {MUERTE, ESTADO_MUERTE}};

void AdministradorVistaJuego::actualizar_vista_fondo_escenario(const TipoEscenario tipo_escenario) {
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
        const std::vector<ClienteDTO>& clientes_recibidos, const int tiempo_restante) {
    if (const auto jugador = std::find_if(clientes_recibidos.begin(), clientes_recibidos.end(),
                                          [this](const auto& cliente) {
                                              return cliente.obtener_id_cliente() ==
                                                     this->id_jugador;
                                          });
        jugador != clientes_recibidos.end()) {
        const int32_t id_recibido = jugador->obtener_id_cliente();
        const TipoPersonaje tipo_personaje_recibido = jugador->obtener_tipo_personaje();
        const int32_t pos_x = jugador->obtener_pos_x();
        const int32_t pos_y = jugador->obtener_pos_y();
        if (personajes.count(id_recibido) == 0) {
            Personaje nuevo_personaje(id_recibido, MAPA_TIPO_PERSONAJE.at(tipo_personaje_recibido),
                                      renderer, lector_texturas, camara, pos_x, pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(id_recibido, std::move(nuevo_personaje));
        }
        personajes.at(id_recibido).actualizar_camara();

        // Actualizar HUD en base a los datos del jugador
        const uint32_t puntos_recibidos = jugador->obtener_puntos();
        const uint32_t vida = jugador->obtener_vida();
        const TipoArma arma_actual = jugador->obtener_arma_actual();
        const int32_t balas_restantes = jugador->obtener_balas_restantes();
        hud.actualizar(tipo_personaje_recibido, puntos_recibidos, vida, arma_actual,
                       balas_restantes, tiempo_restante);
    }

    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> datos_jugadores(
            clientes_recibidos.size());
    std::transform(clientes_recibidos.begin(), clientes_recibidos.end(), datos_jugadores.begin(),
                   [](const ClienteDTO& p) {
                       return std::make_tuple(p.obtener_id_cliente(), p.obtener_puntos(),
                                              p.obtener_tipo_personaje());
                   });
    hud.actualizar_top_jugadores(std::move(datos_jugadores));
}

void AdministradorVistaJuego::actualizar_vista_bloques_escenario(
        const std::vector<BloqueEscenarioDTO>& bloques_recibidos) {
    if (!bloques_recibidos.empty()) {
        for (auto bloque: bloques_recibidos) {
            SDL2pp::Texture& textura_bloque =
                    lector_texturas.obtener_textura_bloque(MAPA_TIPO_ESCENARIO.at(tipo_escenario));
            const SDL2pp::Rect& coords_textura = lector_texturas.obtener_coords_bloque(
                    MAPA_TIPO_ESCENARIO.at(tipo_escenario),
                    MAPA_TIPO_BLOQUE.at(bloque.obtener_tipo()));

            const int32_t pos_x = bloque.obtener_pos_x();
            const int32_t pos_y = bloque.obtener_pos_y();
            const uint32_t ancho = bloque.obtener_ancho();
            const uint32_t alto = bloque.obtener_alto();

            bloques_escenario.emplace(proximo_id,
                                      std::make_unique<BloqueEscenario>(
                                              SDL2pp::Rect(pos_x, pos_y, static_cast<int>(ancho),
                                                           static_cast<int>(alto)),
                                              renderer, textura_bloque, coords_textura, camara));
            proximo_id++;
        }
    }

    for (auto& [id, bloque]: bloques_escenario) {
        bloque->actualizar_vista();
    }
}

void AdministradorVistaJuego::actualizar_vista_personajes(
        const std::vector<ClienteDTO>& clientes_recibidos) {
    std::unordered_set<uint32_t> ids_clientes_recibidos;
    for (auto c: clientes_recibidos) {
        const int32_t id = c.obtener_id_cliente();
        const TipoPersonaje tipo_recibido = c.obtener_tipo_personaje();
        const int32_t pos_x = c.obtener_pos_x();
        const int32_t pos_y = c.obtener_pos_y();
        const EstadoPersonaje estado = c.obtener_estado();
        const bool de_espaldas = c.obtener_de_espaldas();

        ids_clientes_recibidos.insert(id);
        if (personajes.count(id) == 0) {
            Personaje nuevo_personaje(id, MAPA_TIPO_PERSONAJE.at(tipo_recibido), renderer,
                                      lector_texturas, camara, pos_x, pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(id, std::move(nuevo_personaje));
        }

        personajes.at(id).actualizar_animacion(
                MAPA_ESTADOS_PERSONAJE.at(estado), iteraciones_actuales,
                {pos_x, pos_y, FACTOR_ESCALA_SPRITES, FACTOR_ESCALA_SPRITES}, 0, de_espaldas);
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
        const int32_t id = enemigo.obtener_id();
        const TipoEnemigo tipo = enemigo.obtener_tipo();
        const int32_t pos_x = enemigo.obtener_pos_x();
        const int32_t pos_y = enemigo.obtener_pos_y();
        const int32_t ancho = enemigo.obtener_ancho();
        const int32_t alto = enemigo.obtener_alto();
        const bool invertido = enemigo.obtener_invertido();

        if (!enemigos.existe_enemigo(id)) {
            enemigos.agregar_enemigo(id, tipo,
                                     {pos_x, pos_y, FACTOR_ESCALA_SPRITES, FACTOR_ESCALA_SPRITES},
                                     invertido);
        }
        enemigos.actualizar_animacion(id, iteraciones_actuales, {pos_x, pos_y, ancho, alto},
                                      invertido);
    }
}

void AdministradorVistaJuego::actualizar_vista_balas_y_explosiones(
        const std::vector<BalaDTO>& balas_recibidas) {
    balas.eliminar_balas();
    for (const auto& bala: balas_recibidas) {
        const TipoArma tipo = bala.obtener_tipo();
        const int32_t pos_x = bala.obtener_pos_x();
        const int32_t pos_y = bala.obtener_pos_y();
        const bool choco = bala.obtener_choco();

        balas.agregar_bala(tipo, pos_x, pos_y);
        if (choco) {
            if (tipo == ARMA2) {
                admin_sonidos.preparar_sonido(SONIDO_EXPLOSION, iteraciones_actuales);
                explosiones.agregar_explosion(pos_x, pos_y);
                continue;
            }
            admin_sonidos.preparar_sonido(SONIDO_IMPACTO_BALA, iteraciones_actuales);
        }
    }
    explosiones.actualizar_animacion(iteraciones_actuales);
}

void AdministradorVistaJuego::actualizar_vista_recogibles(
        const std::vector<RecogibleDTO>& recogibles_recibidos) {
    recogibles.eliminar_recogibles();
    for (const auto& recogible: recogibles_recibidos) {
        const TipoRecogible tipo = recogible.obtener_tipo();
        const int32_t pos_x = recogible.obtener_pos_x();
        const int32_t pos_y = recogible.obtener_pos_y();
        const int32_t ancho = recogible.obtener_ancho();
        const int32_t alto = recogible.obtener_alto();

        recogibles.agregar_recogible(tipo, {pos_x, pos_y, ancho, alto});
    }
}

void AdministradorVistaJuego::actualizar_sonidos(const std::shared_ptr<SnapshotDTO>& snapshot) {
    if (snapshot->obtener_hubo_disparo()) {
        admin_sonidos.preparar_sonido(SONIDO_DISPARO, iteraciones_actuales);
    }
    if (snapshot->obtener_hubo_herido()) {
        admin_sonidos.preparar_sonido(SONIDO_DANIO, iteraciones_actuales);
    }
    if (snapshot->obtener_hubo_muerte()) {
        admin_sonidos.preparar_sonido(SONIDO_MUERTE, iteraciones_actuales);
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
        // Se procesan los sonidos de todas las snapshots, incluso las descartadas
        actualizar_sonidos(snapshot);
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
    actualizar_vista_camara_y_hud(clientes_recibidos, snapshot->obtener_tiempo_restante());
    actualizar_vista_personajes(clientes_recibidos);
    actualizar_vista_bloques_escenario(snapshot->obtener_bloques_escenario());
    actualizar_vista_personajes(clientes_recibidos);
    actualizar_vista_enemigos(snapshot->obtener_enemigos());
    actualizar_vista_balas_y_explosiones(snapshot->obtener_balas());
    actualizar_vista_recogibles(snapshot->obtener_recogibles());
    actualizar_sonidos(snapshot);
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
        sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
        lector_texturas(renderer),
        entrada_juego(cliente),
        hud(id_cliente, renderer, lector_texturas),
        cliente(cliente),
        iteraciones_actuales(0),
        tipo_escenario(ESCENARIO_INDEFINIDO),
        enemigos(renderer, lector_texturas, camara),
        balas(renderer, lector_texturas, camara),
        recogibles(renderer, lector_texturas, camara),
        explosiones(renderer, lector_texturas, camara),
        reproductor_musica(mixer),
        admin_sonidos(mixer),
        primera_snapshot_recibida(false),
        fin_juego(false) {
    lector_texturas.cargar_texturas_y_coordenadas();
    mixer.SetVolume(-1, VOLUMEN_SONIDOS);
}

void AdministradorVistaJuego::run() {
    int64_t ticks_anteriores = 0;
    bool cerrar_juego = false;

    while (!cerrar_juego) {
        cerrar_juego = !entrada_juego.procesar_entrada();
        if (cerrar_juego) {
            continue;
        }

        actualizar_vista();
        renderer.Clear();

        if (fin_juego) {
            hud.dibujar_pantalla_fin_juego();
            renderer.Present();

            if (reproductor_musica.esta_reproduciendo_musica_ambiente()) {
                reproductor_musica.detener_musica_ambiente();
                reproductor_musica.reproducir_musica_fin_juego();
            }

            const int64_t ticks_actuales = SDL_GetTicks();
            ticks_anteriores += sincronizar_vista(ticks_actuales - ticks_anteriores);
            continue;
        }

        if (fondo_escenario) {
            fondo_escenario->dibujar();
        }
        for (auto& [fst, snd]: bloques_escenario) {
            snd->dibujar();
        }
        recogibles.dibujar_recogibles();
        balas.dibujar_balas();
        enemigos.dibujar_enemigos();
        explosiones.dibujar();

        for (auto& [fst, snd]: personajes) {
            snd.dibujar();
        }

        admin_sonidos.reproducir_sonidos();

        if (primera_snapshot_recibida) {
            hud.dibujar();
            if (entrada_juego.mostrar_top()) {
                hud.dibujar_top_jugadores(false);
            }
            if (!reproductor_musica.esta_reproduciendo_musica_ambiente()) {
                reproductor_musica.reproducir_musica_ambiente(tipo_escenario);
            }
        } else {
            hud.dibujar_pantalla_carga();
        }

        renderer.Present();

        const int64_t ticks_actuales = SDL_GetTicks();
        ticks_anteriores += sincronizar_vista(ticks_actuales - ticks_anteriores);
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
