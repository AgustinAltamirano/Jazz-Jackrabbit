#include "bloque_escenario.h"

BloqueEscenario::BloqueEscenario(const SDL2pp::Rect coords, SDL2pp::Renderer& renderer,
                                 SDL2pp::Texture& textura, const SDL2pp::Rect& coords_textura,
                                 const Camara& camara):
        coords(coords),
        render_coords(camara.obtener_coords_ventana(coords)),
        renderer(renderer),
        textura(textura),
        coords_textura(coords_textura),
        camara(camara) {}

void BloqueEscenario::actualizar_vista() { render_coords = camara.obtener_coords_ventana(coords); }

void BloqueEscenario::dibujar() const {
    const int ancho_textura = coords_textura.GetW();
    const int alto_textura = coords_textura.GetH();

    for (int x = render_coords.GetX(); x < render_coords.GetX() + render_coords.GetW();
         x += ancho_textura) {
        for (int y = render_coords.GetY(); y < render_coords.GetY() + render_coords.GetH();
             y += alto_textura) {
            const SDL2pp::Rect coords_bloque(x, y, ancho_textura, alto_textura);
            if (!Camara::esta_dentro_de_ventana(coords_bloque)) {
                continue;
            }
            renderer.Copy(textura, coords_textura, coords_bloque);
        }
    }
}

BloqueEscenario::~BloqueEscenario() = default;
