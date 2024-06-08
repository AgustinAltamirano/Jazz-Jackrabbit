#ifndef CAMARA_H
#define CAMARA_H

#include <SDL2pp/SDL2pp.hh>

#include "vista_juego_defs.h"

class Camara {
private:
    /** Posición de la cámara en el escenario del servidor
     * (no confundir con la posición de la cámara en pantalla) */
    int pos_camara_x, pos_camara_y;

    static bool comprobar_pos_relativa(int pos_relativa_x, int pos_relativa_y);

public:
    Camara();

    Camara(int pos_camara_x, int pos_camara_y);

    Camara(const Camara&) = delete;

    Camara& operator=(const Camara&) = delete;

    void actualizar_pos_camara(int pos_camara_x, int pos_camara_y);

    [[nodiscard]] static bool esta_dentro_de_ventana(const SDL2pp::Rect& coords);

    [[nodiscard]] SDL2pp::Rect obtener_coords_ventana(const SDL2pp::Rect& coords) const;

    ~Camara();
};

#endif  // CAMARA_H
