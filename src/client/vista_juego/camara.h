#ifndef CAMARA_H
#define CAMARA_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_juego_defs.h"

/**
 * @class Camara
 * @brief Clase que representa la cámara del jugador en el juego. Determina las coordenadas de la
 * ventana donde debe renderizarse cada elemento visual del juego, además de decidir cuáles deben
 * hacerlo y cuáles no.
 */
class Camara {
private:
    /** Posición de la cámara en el escenario del servidor
     * (no confundir con la posición de la cámara en pantalla) */
    int pos_camara_x, pos_camara_y;

    /**
     * @brief Comprueba la posición relativa de un elemento visual respecto de la posición de la
     * cámara
     * @param pos_relativa_x Posición relativa en el eje X.
     * @param pos_relativa_y Posición relativa en el eje Y.
     * @return true si la posición se encuentra dentro de la ventana, false en caso contrario.
     */
    static bool comprobar_pos_relativa(int pos_relativa_x, int pos_relativa_y);

public:
    Camara();

    Camara(int pos_camara_x, int pos_camara_y);

    Camara(const Camara&) = delete;

    Camara& operator=(const Camara&) = delete;

    /**
     * @brief Actualiza la posición de la cámara.
     * @param pos_camara_x Nueva posición de la cámara en el eje X (coordenadas de lógica de juego).
     * @param pos_camara_y Nueva posición de la cámara en el eje Y (coordenadas de lógica de juego).
     */
    void actualizar_pos_camara(int pos_camara_x, int pos_camara_y);

    /**
     * @brief Comprueba si el rectángulo se encuentra al menos en parte dentro de la ventana.
     * @param coords Rectángulo con las coordenadas a comprobar.
     * @return true si las coordenadas están dentro de la ventana, false en caso contrario.
     */
    [[nodiscard]] static bool esta_dentro_de_ventana(const SDL2pp::Rect& coords);

    /**
     * @brief Obtiene las coordenadas de un objeto en la ventana a partir de sus coordenadas de
     * lógica de juego
     * @param coords Coordenadas del objeto en la lógica de juego.
     * @return Rectángulo con las coordenadas transformadas.
     */
    [[nodiscard]] SDL2pp::Rect obtener_coords_ventana(const SDL2pp::Rect& coords) const;

    ~Camara();
};

#endif  // CAMARA_H
