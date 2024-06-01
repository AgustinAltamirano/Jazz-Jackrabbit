#ifndef BLOQUE_ESCENARIO_H
#define BLOQUE_ESCENARIO_H

#include <SDL2pp/SDL2pp.hh>

class BloqueEscenario {
protected:
    const int render_x, render_y, render_ancho, render_alto;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture &textura_superficie, &textura_relleno;
    const SDL2pp::Rect& coords_superficie;
    const SDL2pp::Rect& coords_relleno;

public:
    BloqueEscenario(int render_x, int render_y, int render_ancho, int render_alto,
                    SDL2pp::Renderer& renderer, SDL2pp::Texture& textura_superficie,
                    SDL2pp::Texture& textura_relleno, const SDL2pp::Rect& coords_superficie,
                    const SDL2pp::Rect& coords_relleno);

    BloqueEscenario(const BloqueEscenario&) = delete;

    BloqueEscenario& operator=(const BloqueEscenario&) = delete;

    virtual void dibujar() const = 0;

    virtual ~BloqueEscenario();
};

#endif  // BLOQUE_ESCENARIO_H
