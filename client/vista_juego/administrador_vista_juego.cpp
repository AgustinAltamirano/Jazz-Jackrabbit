#include "administrador_vista_juego.h"

#include <utility>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "personaje_jazz.h"

AdministradorVistaJuego::AdministradorVistaJuego(const std::string& titulo_ventana,
                                                 Queue<int>& cola_acciones):
        proximo_id(0),
        sdl(SDL_INIT_VIDEO),
        ventana(titulo_ventana, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA,
                ALTO_VENTANA, 0),
        renderer(ventana, -1, SDL_RENDERER_ACCELERATED),
        lector_texturas(renderer),
        entrada_juego(cola_acciones) {
    lector_texturas.cargar_texturas_y_coordenadas();

    const std::vector<SDL2pp::Rect>& sprite_coords =
            lector_texturas.obtener_coords_personaje("jazz", "stand");
    const std::vector<int> dimensiones_iniciales = {X_INICIAL, Y_INICIAL,
                                                    sprite_coords.at(0).GetW() * 2,
                                                    sprite_coords.at(0).GetH() * 2, 0};
    PersonajeJazz jazz(proximo_id, renderer, lector_texturas, dimensiones_iniciales,
                       FRAMES_POR_SPRITE, SDL_GetTicks());
    personajes.emplace(proximo_id, std::move(jazz));
    proximo_id++;

    const std::vector<SDL2pp::Rect>& sprite_coords2 =
            lector_texturas.obtener_coords_personaje("jazz", "correr");
    const std::vector<int> dimensiones_iniciales2 = {X_INICIAL2, Y_INICIAL2,
                                                     sprite_coords.at(0).GetW() * 2,
                                                     sprite_coords.at(0).GetH() * 2, 0};
    PersonajeJazz jazz2(proximo_id, renderer, lector_texturas, dimensiones_iniciales2,
                        FRAMES_POR_SPRITE, SDL_GetTicks());
    personajes.emplace(proximo_id, std::move(jazz2));
    proximo_id++;

    const std::vector<SDL2pp::Rect>& sprite_coords3 =
            lector_texturas.obtener_coords_personaje("jazz", "disparar");
    const std::vector<int> dimensiones_iniciales3 = {X_INICIAL3, Y_INICIAL3,
                                                     sprite_coords.at(0).GetW() * 2,
                                                     sprite_coords.at(0).GetH() * 2, 0};
    PersonajeJazz jazz3(proximo_id, renderer, lector_texturas, dimensiones_iniciales3,
                        FRAMES_POR_SPRITE, SDL_GetTicks());
    personajes.emplace(proximo_id, std::move(jazz3));
    proximo_id++;

    const std::vector<SDL2pp::Rect>& sprite_coords4 =
            lector_texturas.obtener_coords_personaje("jazz", "caer_abajo");
    const std::vector<int> dimensiones_iniciales4 = {X_INICIAL4, Y_INICIAL4,
                                                     sprite_coords.at(0).GetW() * 2,
                                                     sprite_coords.at(0).GetH() * 2, 0};
    PersonajeJazz jazz4(proximo_id, renderer, lector_texturas, dimensiones_iniciales4,
                        FRAMES_POR_SPRITE, SDL_GetTicks());
    personajes.emplace(proximo_id, std::move(jazz4));
    proximo_id++;
}

void AdministradorVistaJuego::run() {
    // Como primera prueba, se renderiza únicamente un objeto visual con animación
    // que no cambia su posición.
    bool close = false;
    const std::vector<int> dimensiones = {X_INICIAL, Y_INICIAL, 4, 4, 0};
    const std::vector<int> dimensiones2 = {X_INICIAL2, Y_INICIAL2, 4, 4, 0};
    const std::vector<int> dimensiones3 = {X_INICIAL3, Y_INICIAL3, 4, 4, 0};
    const std::vector<int> dimensiones4 = {X_INICIAL4, Y_INICIAL4, 4, 4, 0};
    uint32_t ticks_anteriores = SDL_GetTicks();
    while (!close) {
        const uint32_t frame_ticks = SDL_GetTicks();
        const uint32_t frame_ticks_transcurridos = frame_ticks - ticks_anteriores;
        ticks_anteriores = frame_ticks;

        renderer.Clear();
        personajes.at(0).actualizar_animacion(STAND, frame_ticks_transcurridos, dimensiones);
        personajes.at(0).dibujar();

        personajes.at(1).actualizar_animacion(CORRER, frame_ticks_transcurridos, dimensiones2);
        personajes.at(1).dibujar();

        personajes.at(2).actualizar_animacion(DISPARAR, frame_ticks_transcurridos, dimensiones3);
        personajes.at(2).dibujar();

        personajes.at(3).actualizar_animacion(CAER_ABAJO, frame_ticks_transcurridos, dimensiones4);
        personajes.at(3).dibujar();
        renderer.Present();

        entrada_juego.procesar_entrada();

        if (frame_ticks > 100000000) {
            close = true;
        }
    }
}

AdministradorVistaJuego::~AdministradorVistaJuego() = default;
