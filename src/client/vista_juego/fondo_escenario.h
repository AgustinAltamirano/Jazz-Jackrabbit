#ifndef FONDO_ESCENARIO_H
#define FONDO_ESCENARIO_H

#include <SDL2pp/SDL2pp.hh>

/** Clase que representa el fondo visual del escenario dentro del juego. */
class FondoEscenario {
private:
    const int ancho_ventana, alto_ventana;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture& textura;
    const SDL2pp::Rect& coords_textura;

public:
    FondoEscenario(int ancho_ventana, int alto_ventana, SDL2pp::Renderer& renderer,
                   SDL2pp::Texture& textura, const SDL2pp::Rect& coords_textura);

    FondoEscenario(const FondoEscenario&) = delete;

    FondoEscenario& operator=(const FondoEscenario&) = delete;

    void dibujar() const;

    ~FondoEscenario();
};

#endif  // FONDO_ESCENARIO_H
