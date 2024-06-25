#ifndef ADMIN_EXPLOSIONES_H
#define ADMIN_EXPLOSIONES_H

#include <cstdint>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "lector_texturas.h"
#include "objeto_animado.h"

/**
 * @class AdminExplosiones
 * @brief Clase encargada de administrar la vista de todas las explosiones presentes en el juego.
 */
class AdminExplosiones {
private:
    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;

    /** Mapa con todas las explosiones presentes en el juego */
    std::unordered_map<uint32_t, ObjetoAnimado> explosiones;

    /** Mapa con las coordenadas de todas las explosiones presentes en el juego */
    std::unordered_map<uint32_t, SDL2pp::Rect> posicion_explosiones;
    const uint16_t cantidad_frames_explosion;
    uint32_t siguiente_id_explosion;

    /**
     * @brief Corrige el desfase entre el sprite de la explosión y las coordenadas de la explosión
     * en la lógica del juego, de forma que el sprite se dibuje centrado respecto a esas
     * coordenadas.
     * @param coords_sprite Coordenadas del sprite
     * @param pos_x Posición x de la explosión en la lógica del juego
     * @param pos_y Posición y de la explosión en la lógica del juego
     * @return Rectángulo con las coordenadas corregidas donde se debe renderizar el sprite
     */
    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              int32_t pos_x, int32_t pos_y);

public:
    AdminExplosiones(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminExplosiones(const AdminExplosiones&) = delete;
    AdminExplosiones& operator=(const AdminExplosiones&) = delete;

    /**
     * @brief Agrega una explosión al juego
     * @param pos_x Posición x de la explosión
     * @param pos_y Posición y de la explosión
     */
    void agregar_explosion(int pos_x, int pos_y);

    /**
     * @brief Actualiza la animación de todas las explosiones del juego
     * @param iteraciones_actuales Número de iteraciones actuales del juego
     */
    void actualizar_animacion(uint32_t iteraciones_actuales);

    /**
     * @brief Dibuja todas las explosiones
     */
    void dibujar();

    ~AdminExplosiones();
};


#endif  // ADMIN_EXPLOSIONES_H
