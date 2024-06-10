#include "recogible.h"

recogible::recogible(int32_t x, int32_t y, uint32_t ancho, uint32_t alto, TipoRecogible tipo):
        pos_x(x), pos_y(y), ancho(ancho), alto(alto), tipo(tipo) {
    switch (tipo) {
        case GEMA_AGARRABLE:
            this->valor = PUNTOS_GEMA;
        case MONEDA_AGARRABLE:
            this->valor = PUNTOS_MONEDA;
        case MUNICION_ARMA_1:
            this->valor = MUNICIONES_ARMA1;
        case MUNICION_ARMA_2:
            this->valor = MUNICIONES_ARMA2;
        case MUNICION_ARMA_3:
            this->valor = MUNICIONES_ARMA3;
        default:
            this->valor = VIDA_COMIDA;
    }
}

uint32_t recogible::chequear_colision(const int32_t pos_x, const int32_t pos_y,
                                      const uint32_t ancho, const uint32_t alto) const {
    const int32_t punto_x = this->pos_x + this->ancho / 2;
    const int32_t punto_y = this->pos_y + this->alto / 2;
    if ((pos_x < punto_x < pos_x + ancho) && (pos_y < punto_y < pos_y + alto)) {
        return this->valor;
    }
    return 0;
}

TipoRecogible recogible::get_objeto() const { return tipo; }
