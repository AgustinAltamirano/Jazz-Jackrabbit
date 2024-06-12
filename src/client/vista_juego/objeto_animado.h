#ifndef OBJETO_ANIMADO_H
#define OBJETO_ANIMADO_H
#include <cstdint>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "camara.h"

/** La clase ObjetoAnimado modela un objeto visual genérico con animación. */
class ObjetoAnimado {
private:
    const uint32_t id;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture& textura;
    Camara& camara;

    /**
     * Vector con los rectángulos de cada uno de los sprites usados en la animación.
     * Cada rectángulo indica las medidas (posición x e y, ancho y alto) que se debe recortar de
     * @code textura@endcode para formar cada uno de los sprites. La longitud de este vector indica
     * la cantidad de sprites que utiliza el objeto.
     */
    const std::vector<SDL2pp::Rect>& sprite_coords;

    /**
     * Dimensiones y coordenadas donde debe ser renderizado el objeto.
     */
    SDL2pp::Rect render_coords;

    int render_angulo;

    /** Determina si el objeto se debe renderizar invertido horizontalmente o no */
    bool invertido;

    bool reseteado;

    /** Índice del sprite actual en @code sprite_coords@endcode. */
    uint16_t sprite_actual;

    const uint32_t iteraciones_por_sprite;

public:
    ObjetoAnimado(uint32_t id, SDL2pp::Renderer& renderer, SDL2pp::Texture& textura,
                  const std::vector<SDL2pp::Rect>& sprite_coords, Camara& camara,
                  const SDL2pp::Rect& dimensiones_iniciales, int angulo,
                  uint32_t iteraciones_por_sprite);

    ObjetoAnimado(const ObjetoAnimado&) = delete;

    ObjetoAnimado& operator=(const ObjetoAnimado&) = delete;

    ObjetoAnimado(ObjetoAnimado&& otro) noexcept;

    ObjetoAnimado& operator=(ObjetoAnimado&& otro) = delete;

    [[nodiscard]] const SDL2pp::Rect& obtener_coords_sprite_actual() const;

    void resetear_animacion();

    void actualizar_iteracion(uint32_t iteraciones_actuales);

    /**
     * Actualiza el sprite actual, así como su posición y dimensiones.
     * @param dimensiones Nuevas dimensiones y posición del objeto
     * @param angulo Nuevo ángulo del objeto
     * @param invertido Determina si el sprite debe dibujarse invertido horizontalmente o no
     */
    void actualizar_animacion(const SDL2pp::Rect& dimensiones, int angulo, bool invertido);

    void actualizar_camara(int camara_pos_x, int camara_pos_y) const;

    /**
     * Incluye al objeto actual en el renderer para su posterior renderización.
     */
    void dibujar() const;

    ~ObjetoAnimado();
};

#endif  // OBJETO_ANIMADO_H
