#include "pantalla_carga.h"

#include "vista_juego_defs.h"

PantallaCarga::PantallaCarga(SDL2pp::Renderer& renderer):
        renderer(renderer),
        textura(renderer, SDL_PIXELFORMAT_BGR888, SDL_TEXTUREACCESS_STATIC, 1, 1) {
    constexpr unsigned char brillo[] = {255};
    textura.Update(SDL2pp::NullOpt, brillo, 3)
            .SetColorMod(COLOR_PANTALLA_CARGA_RED, COLOR_PANTALLA_CARGA_GREEN,
                         COLOR_KEY_ENEMIGOS_BLUE);
}

void PantallaCarga::dibujar() {
    renderer.Copy(textura, SDL2pp::NullOpt, SDL2pp::Rect(0, 0, ANCHO_VENTANA, ALTO_VENTANA));
}
PantallaCarga::~PantallaCarga() = default;
