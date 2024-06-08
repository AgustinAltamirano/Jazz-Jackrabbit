#ifndef PARED_ESCENARIO_H
#define PARED_ESCENARIO_H

#include "bloque_escenario.h"

class ParedEscenario final: public BloqueEscenario {
public:
    ParedEscenario(SDL2pp::Rect coords, SDL2pp::Renderer& renderer,
                   SDL2pp::Texture& textura_superficie, SDL2pp::Texture& textura_relleno,
                   const SDL2pp::Rect& coords_superficie, const SDL2pp::Rect& coords_relleno,
                   const Camara& camara);

    ParedEscenario(const ParedEscenario&) = delete;

    ParedEscenario& operator=(const ParedEscenario&) = delete;

    void dibujar() const override;

    ~ParedEscenario() override;
};


#endif  // PARED_ESCENARIO_H
