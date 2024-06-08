#include "pared_escenario.h"

ParedEscenario::ParedEscenario(const SDL2pp::Rect coords, SDL2pp::Renderer& renderer,
                               SDL2pp::Texture& textura_superficie,
                               SDL2pp::Texture& textura_relleno,
                               const SDL2pp::Rect& coords_superficie,
                               const SDL2pp::Rect& coords_relleno, const Camara& camara):
        BloqueEscenario(coords, renderer, textura_superficie, textura_relleno, coords_superficie,
                        coords_relleno, camara) {}

void ParedEscenario::dibujar() const {
    const int ancho_textura_superficie = coords_superficie.GetW();
    const int alto_textura_superficie = coords_superficie.GetH();
    const int ancho_textura_relleno = coords_relleno.GetW();
    const int alto_textura_relleno = coords_relleno.GetH();

    for (int y = render_coords.GetY(); y < render_coords.GetY() + render_coords.GetH();
         y += alto_textura_superficie) {
        const SDL2pp::Rect coords_bloque(render_coords.GetX(), y, ancho_textura_superficie,
                                         alto_textura_superficie);
        if (!Camara::esta_dentro_de_ventana(coords_bloque)) {
            continue;
        }
        renderer.Copy(textura_superficie, coords_superficie, coords_bloque);
    }

    for (int x = render_coords.GetX() + ancho_textura_superficie;
         x < render_coords.GetX() + render_coords.GetW(); x += ancho_textura_relleno) {
        for (int y = render_coords.GetY(); y < render_coords.GetY() + render_coords.GetH();
             y += alto_textura_relleno) {
            const SDL2pp::Rect coords_bloque(x, y, ancho_textura_relleno, alto_textura_relleno);
            if (!Camara::esta_dentro_de_ventana(coords_bloque)) {
                continue;
            }
            renderer.Copy(textura_relleno, coords_relleno, coords_bloque);
        }
    }
}

ParedEscenario::~ParedEscenario() = default;
