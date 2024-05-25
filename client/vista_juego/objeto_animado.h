#ifndef OBJETO_ANIMADO_H
#define OBJETO_ANIMADO_H
#include <cstdint>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

/** Los vectores de dimensiones deben contener
 * la posición en x, en y, el ancho, alto y el ángulo.
 */
#define CANTIDAD_PARAM_DIMENSIONES 5

enum pos_dimension : uint8_t {
    RENDER_X = 0,
    RENDER_Y,
    RENDER_ANCHO,
    RENDER_ALTO,
    RENDER_ANGULO,
};

/** La clase ObjetoAnimado modela un objeto visual genérico con animación. */
class ObjetoAnimado {
private:
    const uint32_t id;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture& textura;

    /**
     * Vector con los rectángulos de cada uno de los sprites usados en la animación.
     * Cada rectángulo indica las medidas (posición x e y, ancho y alto) que se debe recortar de
     * @code textura@endcode para formar cada uno de los sprites. La longitud de este vector indica
     * la cantidad de sprites que utiliza el objeto.
     */
    const std::vector<SDL2pp::Rect>& sprite_coords;

    /**
     * Dimensiones y coordenadas donde debe ser renderizado el objeto.
     * - @code render_x@endcode: posición horizontal del objeto
     * - @code render_y@endcode: posición vertical del objeto
     * - @code render_ancho@endcode: ancho del objeto
     * - @code render_alto@endcode: alto del objeto
     * - @code render_angulo@endcode: ángulo de rotación del objeto (respecto a su textura original)
     */
    int render_x, render_y, render_ancho, render_alto, render_angulo;

    /** Determina si el objeto se debe renderizar invertido horizontalmente o no */
    bool invertido;

    /** Índice del sprite actual en @code sprite_coords@endcode. */
    uint16_t sprite_actual;

    const unsigned int frames_por_sprite;
    unsigned int frame_ticks_anteriores;

public:
    ObjetoAnimado(uint32_t id, SDL2pp::Renderer& renderer, SDL2pp::Texture& textura,
                  const std::vector<SDL2pp::Rect>& sprite_coords,
                  const std::vector<int>& dimensiones_iniciales, unsigned int frames_por_sprite,
                  unsigned int frame_ticks_actuales);

    ObjetoAnimado(const ObjetoAnimado&) = delete;

    ObjetoAnimado& operator=(const ObjetoAnimado&) = delete;

    ObjetoAnimado(ObjetoAnimado&& otro) noexcept;

    ObjetoAnimado& operator=(ObjetoAnimado&& otro) = delete;

    void resetear_animacion();

    /**
     * Actualiza el sprite actual, así como su posición y dimensiones.
     * @param frame_ticks_transcurridos Cantidad de frames transcurridos desde la última
     * actualización
     * @param dimensiones Nuevas dimensiones y posición del objeto
     */
    void actualizar_animacion(unsigned int frame_ticks_transcurridos,
                              const std::vector<int>& dimensiones);

    /**
     * Incluye al objeto actual en el renderer para su posterior renderización.
     */
    void dibujar() const;

    ~ObjetoAnimado();
};

#endif  // OBJETO_ANIMADO_H
