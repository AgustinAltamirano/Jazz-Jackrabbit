#include "administrador_vista_juego.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "personaje_jazz.h"

AdministradorVistaJuego::AdministradorVistaJuego(
        const std::string& titulo_ventana, Queue<AccionJuegoDTO>& cola_acciones,
        Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots):
        proximo_id(0),
        sdl(SDL_INIT_VIDEO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        lector_texturas(renderer),
        entrada_juego(cola_acciones),
        cola_snapshots(cola_snapshots) {
    lector_texturas.cargar_texturas_y_coordenadas();
}

void AdministradorVistaJuego::run() {
    bool close = false;
    uint32_t ticks_anteriores = SDL_GetTicks();
    while (!close) {
        const uint32_t frame_ticks = SDL_GetTicks();
        // cppcheck-suppress unreadVariable
        const uint32_t frame_ticks_transcurridos = frame_ticks - ticks_anteriores;
        ticks_anteriores = frame_ticks;

        renderer.Clear();
        renderer.Present();

        entrada_juego.procesar_entrada();

        if (frame_ticks > 100000000) {
            close = true;
        }
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
