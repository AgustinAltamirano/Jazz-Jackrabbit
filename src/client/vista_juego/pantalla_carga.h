#ifndef PANTALLA_CARGA_H
#define PANTALLA_CARGA_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_juego_defs.h"

class PantallaCarga {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture textura;

public:
    explicit PantallaCarga(SDL2pp::Renderer& renderer);

    PantallaCarga(const PantallaCarga&) = delete;
    PantallaCarga& operator=(const PantallaCarga&) = delete;

    void dibujar();

    ~PantallaCarga();
};


#endif  // PANTALLA_CARGA_H
