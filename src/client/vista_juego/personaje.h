#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <string>
#include <unordered_map>

#include "lector_texturas.h"
#include "objeto_animado.h"

typedef enum {
    ESTADO_INDEFINIDO = 0,
    ESTADO_STAND,
    ESTADO_CORRER,
    ESTADO_DASH,
    ESTADO_DISPARAR,
    ESTADO_SALTAR_ARRIBA,
    ESTADO_CAER_ABAJO,
    ESTADO_SALTAR_ADELANTE,
    ESTADO_CAER_ADELANTE,
    ESTADO_ATAQUE_ESPECIAL,
} EstadoVisualPersonaje;


/** Clase que representa un personaje visual dentro del juego. */
class Personaje {
private:
    static const std::unordered_map<EstadoVisualPersonaje, const std::string>
            mapa_estados_personaje;
    const uint32_t id;
    const std::string nombre_personaje;
    EstadoVisualPersonaje estado_actual;
    int pos_x, pos_y, angulo;
    bool invertido;
    const uint32_t iteraciones_por_sprite;

    std::unordered_map<EstadoVisualPersonaje, ObjetoAnimado> animaciones;

    SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& dimensiones) const;

public:
    Personaje(uint32_t id, std::string nombre_personaje, SDL2pp::Renderer& renderer,
              LectorTexturas& lector_texturas, Camara& camara, int pos_x, int pos_y, int angulo,
              uint32_t iteraciones_por_sprite);

    Personaje(const Personaje&) = delete;

    Personaje& operator=(const Personaje&) = delete;

    Personaje(Personaje&& otro) noexcept;

    Personaje& operator=(Personaje&& otro) = delete;

    /**
     * Actualiza la animación del personaje, así como su posición y dimensiones.
     * @param estado estado actual del personaje
     * @param iteraciones_actuales Iteraciones actuales del renderizado del juego
     * @param dimensiones Nuevas dimensiones y posición del personaje
     * @param angulo Nuevo ángulo del personaje
     * @param invertido Determina si la textura debe dibujarse invertida o no
     */
    void actualizar_animacion(EstadoVisualPersonaje estado, uint32_t iteraciones_actuales,
                              const SDL2pp::Rect& dimensiones, int angulo, bool invertido);

    void actualizar_camara() const;

    /**
     * Incluye al personaje en el renderer para su posterior renderización.
     */
    void dibujar() const;

    ~Personaje();
};


#endif  // PERSONAJE_H
