#ifndef RECOGIBLE_H
#define RECOGIBLE_H

#include <cstdint>

#include "../../../common/constantes.h"

typedef enum {
    MONEDA = 0,
    GEMA,
    MUNICION_ARMA_1,
    MUNICION_ARMA_2,
    MUNICION_ARMA_3,
    FRUTA_PODRIDA,
    FRUTA_BUENA,
} TipoRecogible;

class recogible {
private:
    int32_t pos_x;
    int32_t pos_y;
    uint32_t ancho;
    uint32_t alto;
    uint32_t valor;
    TipoRecogible tipo;

public:
    recogible(int32_t x, int32_t y, uint32_t ancho, uint32_t alto, TipoRecogible tipo);
    [[nodiscard]] uint32_t chequear_colision(int32_t pos_x, int32_t pos_y, uint32_t ancho,
                                             uint32_t alto) const;
    [[nodiscard]] TipoRecogible get_objeto() const;
};


#endif  // RECOGIBLE_H
