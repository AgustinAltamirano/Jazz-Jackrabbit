#include "recogible.h"

recogible::recogible(int32_t x, int32_t y, int32_t ancho, int32_t alto, TipoRecogible tipo):
        pos_x(x), pos_y(y), ancho(ancho), alto(alto), tipo(tipo) {
    switch (tipo) {
        case GEMA_AGARRABLE:
            this->valor = PUNTOS_GEMA;
            break;
        case MONEDA_AGARRABLE:
            this->valor = PUNTOS_MONEDA;
            break;
        case MUNICION_ARMA_1:
            this->valor = MUNICIONES_ARMA1;
            break;
        case MUNICION_ARMA_2:
            this->valor = MUNICIONES_ARMA2;
            break;
        case MUNICION_ARMA_3:
            this->valor = MUNICIONES_ARMA3;
            break;
        default:
            this->valor = VIDA_COMIDA;
            break;
    }
}

int32_t recogible::chequear_colision(const int32_t pos_x, const int32_t pos_y, const int32_t ancho,
                                     const int32_t alto) const {
    const int32_t punto_x = this->pos_x + this->ancho / 2;
    const int32_t punto_y = this->pos_y + this->alto / 2;
    if ((pos_x < punto_x < pos_x + ancho) && (pos_y < punto_y < pos_y + alto)) {
        return this->valor;
    }
    return 0;
}

TipoRecogible recogible::get_objeto() const { return tipo; }
