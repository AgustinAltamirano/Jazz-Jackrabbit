#ifndef PISO_ESCENARIO_H
#define PISO_ESCENARIO_H

#include "bloque_escenario.h"

class PisoEscenario final: public BloqueEscenario {
public:
    PisoEscenario(SDL2pp::Rect render_coords, SDL2pp::Renderer& renderer,
                  SDL2pp::Texture& textura_superficie, SDL2pp::Texture& textura_relleno,
                  const SDL2pp::Rect& coords_superficie, const SDL2pp::Rect& coords_relleno,
                  const Camara& camara);

    PisoEscenario(const PisoEscenario&) = delete;

    PisoEscenario& operator=(const PisoEscenario&) = delete;

    void dibujar() const override;

    ~PisoEscenario() override;
};

#endif  // PISO_ESCENARIO_H
