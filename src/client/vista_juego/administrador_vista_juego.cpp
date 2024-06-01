#include "administrador_vista_juego.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

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
}

AdministradorVistaJuego::AdministradorVistaJuego(
        const std::string& titulo_ventana, Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones,
        Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots):
        proximo_id(0),
        sdl(SDL_INIT_VIDEO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        lector_texturas(renderer),
        entrada_juego(cola_acciones),
        cola_snapshots(cola_snapshots),
        tipo_escenario(ESCENARIO_INDEFINIDO) {
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

        actualizar_vista();
        renderer.Clear();
        if (fondo_escenario) {
            fondo_escenario->dibujar();
        }
        renderer.Present();

        entrada_juego.procesar_entrada();

        if (frame_ticks > 100000000) {
            close = true;
        }
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
