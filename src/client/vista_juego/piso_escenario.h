#ifndef PISO_ESCENARIO_H
#define PISO_ESCENARIO_H

#include "bloque_escenario.h"

class PisoEscenario final: public BloqueEscenario {
public:
    PisoEscenario(int render_x, int render_y, int render_ancho, int render_alto,
                  SDL2pp::Renderer& renderer, SDL2pp::Texture& textura_superficie,
                  SDL2pp::Texture& textura_relleno, const SDL2pp::Rect& coords_superficie,
                  const SDL2pp::Rect& coords_relleno);

    PisoEscenario(const PisoEscenario&) = delete;

    PisoEscenario& operator=(const PisoEscenario&) = delete;

    void dibujar() const override;

    ~PisoEscenario() override;
};

#endif  // PISO_ESCENARIO_H
