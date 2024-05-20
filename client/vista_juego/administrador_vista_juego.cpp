#include "administrador_vista_juego.h"

#include <utility>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

AdministradorVistaJuego::AdministradorVistaJuego(const std::string& titulo_ventana):
        proximo_id(0),
        sdl(SDL_INIT_VIDEO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        lector_texturas(renderer) {
    lector_texturas.cargar_texturas_y_coordenadas();
    for (auto iter = lector_texturas.beginPersonajes(); iter != lector_texturas.endPersonajes();
         ++iter) {
        SDL2pp::Texture& textura = iter.obtener_textura_actual();
        const std::vector<SDL2pp::Rect>& sprite_coords = iter.obtener_coordenadas_actuales();
        const std::vector<int> dimensiones_iniciales = {X_INICIAL, Y_INICIAL,
                                                        sprite_coords.at(0).GetW() * 2,
                                                        sprite_coords.at(0).GetH() * 2, 0};
        ObjetoAnimado personaje(proximo_id, renderer, textura, sprite_coords, dimensiones_iniciales,
                                FRAMES_POR_SPRITE, SDL_GetTicks());
        personajes.emplace(proximo_id, std::move(personaje));
        proximo_id++;
    }
}

bool AdministradorVistaJuego::sigue_vivo() { return true; }

void AdministradorVistaJuego::kill() {}

void AdministradorVistaJuego::run() {
    // Como primera prueba, se renderiza únicamente un objeto visual con animación
    // que no cambia su posición.
    bool close = false;
    const std::vector<int> dimensiones = {X_INICIAL, Y_INICIAL, 4, 4, 0};
    uint32_t ticks_anteriores = SDL_GetTicks();
    while (!close) {
        const uint32_t frame_ticks = SDL_GetTicks();
        const uint32_t frame_ticks_transcurridos = frame_ticks - ticks_anteriores;
        ticks_anteriores = frame_ticks;

        renderer.Clear();
        personajes.at(0).actualizar_animacion(frame_ticks_transcurridos, dimensiones);
        personajes.at(0).dibujar();
        renderer.Present();

        if (frame_ticks > 100000000) {
            close = true;
        }
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() { join(); }
