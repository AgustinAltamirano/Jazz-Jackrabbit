#ifndef BLOQUE_ESCENARIO_H
#define BLOQUE_ESCENARIO_H

#include <SDL2pp/SDL2pp.hh>

#include "camara.h"

/**
 * @class BloqueEscenario
 * @brief Clase que representa un bloque del escenario en la vista del juego.
 */
class BloqueEscenario {
private:
    SDL2pp::Rect coords;
    SDL2pp::Rect render_coords;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture& textura;
    const SDL2pp::Rect& coords_textura;
    const Camara& camara;

public:
    BloqueEscenario(SDL2pp::Rect coords, SDL2pp::Renderer& renderer, SDL2pp::Texture& textura,
                    const SDL2pp::Rect& coords_textura, const Camara& camara);

    BloqueEscenario(const BloqueEscenario&) = delete;

    BloqueEscenario& operator=(const BloqueEscenario&) = delete;

    /**
     * @brief Actualiza la vista del bloque
     */
    void actualizar_vista();

    /**
     * @brief Dibuja el bloque
     */
    void dibujar() const;

    ~BloqueEscenario();
};

#endif  // BLOQUE_ESCENARIO_H
