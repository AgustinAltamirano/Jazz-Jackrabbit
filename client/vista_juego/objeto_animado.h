#ifndef OBJETO_ANIMADO_H
#define OBJETO_ANIMADO_H
#include <cstdint>
#include <vector>

#include <SDL2/SDL_render.h>
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

/** La clase modela un objeto visual genérico con animación. */
class ObjetoAnimado {
private:
    /** ID del objeto visual en el juego. */
    const uint32_t id;

    /** Renderer utilizado por el juego para mostrar la interfaz gráfica. */
    SDL2pp::Renderer& renderer;

    /** Textura ya cargada con todos los sprites utilizados por el objeto. */
    SDL2pp::Texture& sprites;

    /**
     * Vector con los rectángulos de cada uno de los sprites usados en la animación.
     * Cada rectángulo indica las medidas (posición x e y, ancho y alto) que se debe recortar de
     * @code sprites@endcode para formar cada uno de los sprites. La longitud de este vector indica
     * la cantidad de sprites que utiliza el objeto.
     */
    const std::vector<SDL2pp::Rect>& sprite_states;

    /**
     * Dimensiones y coordenadas donde debe ser renderizado el objeto.
     * - @code render_x@endcode: posición horizontal del objeto
     * - @code render_y@endcode: posición vertical del objeto
     * - @code render_ancho@endcode: ancho del objeto
     * - @code render_alto@endcode: alto del objeto
     * - @code render_angulo@endcode: ángulo de rotación del objeto (respecto a su textura original)
     */
    int render_x, render_y, render_ancho, render_alto, render_angulo;

    /**
     * Determina si el objeto se debe renderizar invertido horizontalmente o no
     */
    bool invertido;

    /**
     * Índice del sprite actual en @code sprites@endcode.
     */
    uint16_t sprite_actual;

    /**
     * Cantidad de frames que deben transcurrir por sprite.
     */
    const unsigned int frames_por_sprite;

    /**
     * Frame ticks correspondientes a la última actualización de la animación.
     */
    unsigned int frame_ticks_anteriores;

public:
    ObjetoAnimado(uint32_t id, SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites,
                  const std::vector<SDL2pp::Rect>& sprite_states,
                  const std::vector<int>& dimensiones_iniciales, unsigned int frames_por_sprite,
                  unsigned int frame_ticks_actuales);

    ObjetoAnimado(const ObjetoAnimado&) = delete;

    ObjetoAnimado& operator=(const ObjetoAnimado&) = delete;

    /**
     * Resetea el estado actual de la animación.
     */
    void resetear_animacion();

    /**
     * Actualiza el sprite actual, así como su posición y dimensiones.
     * @param frame_ticks_actuales Cantidad de frames transcurridos desde la última actualización
     * @param dimensiones Nuevas dimensiones y posición del objeto
     */
    void actualizar_animacion(unsigned int frame_ticks_actuales,
                              const std::vector<int>& dimensiones);

    /**
     * Incluye al objeto actual en el renderer para su posterior renderización.
     */
    void dibujar() const;

    ~ObjetoAnimado();
};

#endif  // OBJETO_ANIMADO_H
