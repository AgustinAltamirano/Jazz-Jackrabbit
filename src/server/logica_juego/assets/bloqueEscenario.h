#ifndef BLOQUEESCENARIO_H
#define BLOQUEESCENARIO_H

#include <cstdint>

#include "../../../client/vista_juego/snapshot_dto.h"

class bloqueEscenario {
public:
    int32_t pos_x;
    int32_t pos_y;
    uint32_t ancho;
    uint32_t alto;
    uint32_t angulo;
    TipoBloqueEscenario tipo;
    bloqueEscenario(int32_t pos_x, int32_t pos_y, uint32_t ancho, uint32_t alto, int32_t angulo,
                    TipoBloqueEscenario tipo);
};

#endif  // BLOQUEESCENARIO_H
