#ifndef BLOQUE_ESCENARIO_H
#define BLOQUE_ESCENARIO_H

#include <SDL2pp/SDL2pp.hh>

#include "camara.h"

class BloqueEscenario {
protected:
    SDL2pp::Rect render_coords;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture &textura_superficie, &textura_relleno;
    const SDL2pp::Rect& coords_superficie;
    const SDL2pp::Rect& coords_relleno;
    const Camara& camara;

public:
    BloqueEscenario(SDL2pp::Rect coords, SDL2pp::Renderer& renderer,
                    SDL2pp::Texture& textura_superficie, SDL2pp::Texture& textura_relleno,
                    const SDL2pp::Rect& coords_superficie, const SDL2pp::Rect& coords_relleno,
                    const Camara& camara);

    BloqueEscenario(const BloqueEscenario&) = delete;

    BloqueEscenario& operator=(const BloqueEscenario&) = delete;

    virtual void dibujar() const = 0;

    virtual ~BloqueEscenario();
};

#endif  // BLOQUE_ESCENARIO_H
