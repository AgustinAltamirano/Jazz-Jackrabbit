#include "fondo_escenario.h"

FondoEscenario::FondoEscenario(const int ancho_ventana, const int alto_ventana,
                               SDL2pp::Renderer& renderer, SDL2pp::Texture& textura,
                               const SDL2pp::Rect& coords_textura):
        ancho_ventana(ancho_ventana),
        alto_ventana(alto_ventana),
        renderer(renderer),
        textura(textura),
        coords_textura(coords_textura) {}

void FondoEscenario::dibujar() const {
    const int ancho_textura = coords_textura.GetW();
    const int alto_textura = coords_textura.GetH();
    for (int x = 0; x < ancho_ventana; x += ancho_textura) {
        for (int y = 0; y < alto_ventana; y += alto_textura) {
            renderer.Copy(textura, coords_textura, SDL2pp::Rect(x, y, ancho_textura, alto_textura));
        }
    }
}

FondoEscenario::~FondoEscenario() = default;
