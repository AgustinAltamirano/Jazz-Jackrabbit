#include "administrador_vista_juego.h"

#include <chrono>
#include <thread>
#include <unordered_set>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "pared_escenario.h"
#include "piso_escenario.h"
#include "techo_escenario.h"

const std::unordered_map<TipoEscenario, std::string> AdministradorVistaJuego::MAPA_TIPO_ESCENARIO{
        {ESCENARIO1, "castle"},
        {ESCENARIO2, "carrotus"},
};

const std::unordered_map<TipoBloqueEscenario, std::pair<std::string, std::string>>
        AdministradorVistaJuego::MAPA_TIPO_BLOQUE{
                {PARED, {"pared_superficie", "pared_relleno"}},
                {PISO, {"piso_superficie", "piso_relleno"}},
                {TECHO, {"techo_superficie", "techo_relleno"}},
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
        };

void AdministradorVistaJuego::actualizar_vista() {
    std::shared_ptr<SnapshotDTO_provisorio> snapshot;
    if (!cola_snapshots.try_pop(snapshot)) {
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

    id_jugador = snapshot->obtener_id_cliente();
    const std::vector<ClienteDTO> clientes_recibidos = snapshot->obtener_clientes();

    // Actualizar posición de la cámara
    if (const auto it = std::find_if(
                clientes_recibidos.begin(), clientes_recibidos.end(),
                [this](const auto& cliente) { return cliente.id_cliente == this->id_jugador; });
        it != clientes_recibidos.end()) {
        if (personajes.count(it->id_cliente) == 0) {
            Personaje nuevo_personaje(it->id_cliente, MAPA_TIPO_PERSONAJE.at(it->tipo_personaje),
                                      renderer, lector_texturas, camara, it->pos_x, it->pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(it->id_cliente, std::move(nuevo_personaje));
        }
        personajes.at(it->id_cliente).actualizar_camara();
    }

    if (const std::vector<BloqueEscenarioDTO> bloques_recibidos =
                snapshot->obtener_bloques_escenario();
        !bloques_recibidos.empty()) {
        for (auto bloque: bloques_recibidos) {
            SDL2pp::Texture& textura_bloque =
                    lector_texturas.obtener_textura_bloque(MAPA_TIPO_ESCENARIO.at(tipo_escenario));
            const SDL2pp::Rect& coords_superficie = lector_texturas.obtener_coords_bloque(
                    MAPA_TIPO_ESCENARIO.at(tipo_escenario), MAPA_TIPO_BLOQUE.at(bloque.tipo).first);
            const SDL2pp::Rect& coords_relleno =
                    lector_texturas.obtener_coords_bloque(MAPA_TIPO_ESCENARIO.at(tipo_escenario),
                                                          MAPA_TIPO_BLOQUE.at(bloque.tipo).second);
            switch (bloque.tipo) {
                case PISO:
                    bloques_escenario.emplace(proximo_id,
                                              std::make_unique<PisoEscenario>(
                                                      SDL2pp::Rect(bloque.pos_x, bloque.pos_y,
                                                                   static_cast<int>(bloque.ancho),
                                                                   static_cast<int>(bloque.alto)),
                                                      renderer, textura_bloque, textura_bloque,
                                                      coords_superficie, coords_relleno, camara));
                    proximo_id++;
                    break;
                case PARED:
                    bloques_escenario.emplace(proximo_id,
                                              std::make_unique<ParedEscenario>(
                                                      SDL2pp::Rect(bloque.pos_x, bloque.pos_y,
                                                                   static_cast<int>(bloque.ancho),
                                                                   static_cast<int>(bloque.alto)),
                                                      renderer, textura_bloque, textura_bloque,
                                                      coords_superficie, coords_relleno, camara));
                    proximo_id++;
                    break;
                case TECHO:
                    bloques_escenario.emplace(proximo_id,
                                              std::make_unique<TechoEscenario>(
                                                      SDL2pp::Rect(bloque.pos_x, bloque.pos_y,
                                                                   static_cast<int>(bloque.ancho),
                                                                   static_cast<int>(bloque.alto)),
                                                      renderer, textura_bloque, textura_bloque,
                                                      coords_superficie, coords_relleno, camara));
                    proximo_id++;
                    break;
                case DIAGONAL:
                    // Falta implementar
                    break;
            }
        }
    }

    for (auto& [fst, snd]: bloques_escenario) {
        snd->actualizar_vista();
    }

    std::unordered_set<uint32_t> ids_clientes_recibidos;
    for (auto cliente: clientes_recibidos) {
        ids_clientes_recibidos.insert(cliente.id_cliente);
        if (personajes.count(cliente.id_cliente) == 0) {
            Personaje nuevo_personaje(cliente.id_cliente,
                                      MAPA_TIPO_PERSONAJE.at(cliente.tipo_personaje), renderer,
                                      lector_texturas, camara, cliente.pos_x, cliente.pos_y, 0,
                                      ITERACIONES_POR_SPRITE);
            personajes.emplace(cliente.id_cliente, std::move(nuevo_personaje));
        }

        personajes.at(cliente.id_cliente)
                .actualizar_animacion(MAPA_ESTADOS_PERSONAJE.at(cliente.estado),
                                      iteraciones_actuales, {cliente.pos_x, cliente.pos_y, 2, 2, 0},
                                      cliente.de_espaldas);
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

uint32_t AdministradorVistaJuego::sincronizar_vista(const uint32_t ticks_transcurridos) {
    uint32_t ajuste_tiempo_anterior = 0;
    const auto ticks_transcurridos_aux = static_cast<int64_t>(ticks_transcurridos);
    int64_t tiempo_rest = MILISEGUNDOS_POR_FRAME - ticks_transcurridos_aux;
    if (tiempo_rest < 0) {
        const int64_t tiempo_atrasado = -tiempo_rest;
        tiempo_rest = MILISEGUNDOS_POR_FRAME - tiempo_atrasado % MILISEGUNDOS_POR_FRAME;
        ajuste_tiempo_anterior += tiempo_rest + tiempo_atrasado;
        iteraciones_actuales += ajuste_tiempo_anterior / MILISEGUNDOS_POR_FRAME;

        // Debemos droppear frames de animación, algunas snapshots se pierden
        for (int i = 0; i < tiempo_atrasado / MILISEGUNDOS_POR_FRAME; i++) {
            if (std::shared_ptr<SnapshotDTO_provisorio> snapshot;
                !cola_snapshots.try_pop(snapshot)) {
                break;
            }
        }
    }
    SDL_Delay(tiempo_rest);

    ajuste_tiempo_anterior += MILISEGUNDOS_POR_FRAME;
    iteraciones_actuales++;
    return ajuste_tiempo_anterior;
}

AdministradorVistaJuego::AdministradorVistaJuego(
        const std::string& titulo_ventana, Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones,
        Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots):
        id_jugador(0),
        proximo_id(0),
        sdl(SDL_INIT_VIDEO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        lector_texturas(renderer),
        entrada_juego(cola_acciones),
        cola_snapshots(cola_snapshots),
        iteraciones_actuales(0),
        tipo_escenario(ESCENARIO_INDEFINIDO) {
    lector_texturas.cargar_texturas_y_coordenadas();
}

void AdministradorVistaJuego::run() {
    bool close = false;
    uint32_t ticks_anteriores = 0;
    while (!close) {
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
        renderer.Present();

        close = !entrada_juego.procesar_entrada(id_jugador);

        const uint32_t ticks_actuales = SDL_GetTicks();
        ticks_anteriores += sincronizar_vista(ticks_actuales - ticks_anteriores);
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
