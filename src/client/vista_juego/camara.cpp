#include "camara.h"

bool Camara::comprobar_pos_relativa(const int pos_relativa_x, const int pos_relativa_y) {
    return -MARGEN_RENDERIZADO <= pos_relativa_x &&
           pos_relativa_x <= ANCHO_VENTANA + MARGEN_RENDERIZADO &&
           -MARGEN_RENDERIZADO <= pos_relativa_y &&
           pos_relativa_y <= ALTO_VENTANA + MARGEN_RENDERIZADO;
}

Camara::Camara(): pos_camara_x(0), pos_camara_y(0) {}

Camara::Camara(const int pos_camara_x, const int pos_camara_y):
        pos_camara_x(pos_camara_x), pos_camara_y(pos_camara_y) {}

void Camara::actualizar_pos_camara(const int pos_camara_x, const int pos_camara_y) {
    this->pos_camara_x = pos_camara_x;
    this->pos_camara_y = pos_camara_y;
}

bool Camara::esta_dentro_de_ventana(const SDL2pp::Rect& coords) {
    // Esquina superior izquierda del sprite
    int pos_relativa_x = coords.GetX();
    int pos_relativa_y = coords.GetY();
    if (comprobar_pos_relativa(pos_relativa_x, pos_relativa_y)) {
        return true;
    }

    // Esquina superior derecha del sprite
    pos_relativa_x = coords.GetX() + coords.GetW();
    if (comprobar_pos_relativa(pos_relativa_x, pos_relativa_y)) {
        return true;
    }

    // Esquina inferior derecha del sprite
    pos_relativa_y = coords.GetY() + coords.GetH();
    if (comprobar_pos_relativa(pos_relativa_x, pos_relativa_y)) {
        return true;
    }

    // Esquina inferior izquierda del sprite
    pos_relativa_x = coords.GetX();
    return comprobar_pos_relativa(pos_relativa_x, pos_relativa_y);
}

SDL2pp::Rect Camara::obtener_coords_ventana(const SDL2pp::Rect& coords) const {
    return {coords.GetX() - (pos_camara_x - RENDER_CAMARA_X),
            coords.GetY() - (pos_camara_y - RENDER_CAMARA_Y), coords.GetW(), coords.GetH()};
}

Camara::~Camara() = default;
