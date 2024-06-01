#include "techo_escenario.h"

TechoEscenario::TechoEscenario(const int render_x, const int render_y, const int render_ancho,
                               const int render_alto, SDL2pp::Renderer& renderer,
                               SDL2pp::Texture& textura_superficie,
                               SDL2pp::Texture& textura_relleno,
                               const SDL2pp::Rect& coords_superficie,
                               const SDL2pp::Rect& coords_relleno):
        BloqueEscenario(render_x, render_y, render_ancho, render_alto, renderer, textura_superficie,
                        textura_relleno, coords_superficie, coords_relleno) {}

void TechoEscenario::dibujar() const {
    const int ancho_textura_superficie = coords_superficie.GetW();
    const int alto_textura_superficie = coords_superficie.GetH();
    const int ancho_textura_relleno = coords_relleno.GetW();
    const int alto_textura_relleno = coords_relleno.GetH();

    for (int x = render_x; x < render_x + render_ancho; x += ancho_textura_superficie) {
        renderer.Copy(textura_superficie, coords_superficie,
                      SDL2pp::Rect(x, render_y + render_alto - alto_textura_superficie,
                                   ancho_textura_superficie, alto_textura_superficie));
    }

    for (int x = render_x; x < render_x + render_ancho; x += ancho_textura_relleno) {
        for (int y = render_y + render_alto - alto_textura_superficie - alto_textura_relleno;
             y >= render_y; y -= alto_textura_relleno) {
            renderer.Copy(textura_relleno, coords_relleno,
                          SDL2pp::Rect(x, y, ancho_textura_relleno, alto_textura_relleno));
        }
    }
}

TechoEscenario::~TechoEscenario() = default;
