#ifndef TECHO_ESCENARIO_H
#define TECHO_ESCENARIO_H

#include "bloque_escenario.h"

class TechoEscenario final: public BloqueEscenario {
public:
    TechoEscenario(SDL2pp::Rect render_coords, SDL2pp::Renderer& renderer,
                   SDL2pp::Texture& textura_superficie, SDL2pp::Texture& textura_relleno,
                   const SDL2pp::Rect& coords_superficie, const SDL2pp::Rect& coords_relleno,
                   const Camara& camara);

    TechoEscenario(const TechoEscenario&) = delete;

    TechoEscenario& operator=(const TechoEscenario&) = delete;

    void dibujar() const override;

    ~TechoEscenario() override;
};


#endif  // TECHO_ESCENARIO_H
