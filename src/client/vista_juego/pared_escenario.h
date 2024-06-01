#ifndef PARED_ESCENARIO_H
#define PARED_ESCENARIO_H

#include "bloque_escenario.h"

class ParedEscenario final: public BloqueEscenario {
public:
    ParedEscenario(int render_x, int render_y, int render_ancho, int render_alto,
                   SDL2pp::Renderer& renderer, SDL2pp::Texture& textura_superficie,
                   SDL2pp::Texture& textura_relleno, const SDL2pp::Rect& coords_superficie,
                   const SDL2pp::Rect& coords_relleno);

    ParedEscenario(const ParedEscenario&) = delete;

    ParedEscenario& operator=(const ParedEscenario&) = delete;

    void dibujar() const override;

    ~ParedEscenario() override;
};


#endif  // PARED_ESCENARIO_H
