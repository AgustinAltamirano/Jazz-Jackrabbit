#ifndef RECOGIBLE_H
#define RECOGIBLE_H

#include <cstdint>

#include "../../../common/constantes.h"
#include "../../../common/tipo_recogible.h"

class recogible {
private:
    int32_t pos_x;
    int32_t pos_y;
    int32_t ancho;
    int32_t alto;
    int32_t valor;
    TipoRecogible tipo;

public:
    recogible(int32_t x, int32_t y, int32_t ancho, int32_t alto, TipoRecogible tipo);
    [[nodiscard]] int32_t chequear_colision(int32_t pos_x, int32_t pos_y, int32_t ancho,
                                            int32_t alto) const;
    [[nodiscard]] TipoRecogible get_objeto() const;
};


#endif  // RECOGIBLE_H
