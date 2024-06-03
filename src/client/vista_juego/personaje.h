#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <string>
#include <unordered_map>
#include <vector>

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
    int render_x, render_y, render_angulo;
    bool invertido;
    const unsigned int frames_por_sprite;
    unsigned int frame_ticks_anteriores;
    std::unordered_map<EstadoVisualPersonaje, ObjetoAnimado> animaciones;

public:
    Personaje(uint32_t id, std::string nombre_personaje, SDL2pp::Renderer& renderer,
              LectorTexturas& lector_texturas, const Camara& camara, int pos_x, int pos_y,
              int angulo, unsigned int frames_por_sprite, unsigned int frame_ticks_actuales);

    Personaje(const Personaje&) = delete;

    Personaje& operator=(const Personaje&) = delete;

    Personaje(Personaje&& otro) noexcept;

    Personaje& operator=(Personaje&& otro) = delete;

    /**
     * Actualiza la animación del personaje, así como su posición y dimensiones.
     * @param estado estado actual del personaje
     * @param frame_ticks_transcurridos Cantidad de frames transcurridos desde la última
     * actualización
     * @param dimensiones Nuevas dimensiones y posición del objeto
     * @param invertido Determina si la textura debe dibujarse invertida o no
     */
    void actualizar_animacion(EstadoVisualPersonaje estado, unsigned int frame_ticks_transcurridos,
                              const std::vector<int>& dimensiones, bool invertido);

    /**
     * Incluye al personaje en el renderer para su posterior renderización.
     */
    void dibujar() const;

    ~Personaje();
};


#endif  // PERSONAJE_H
