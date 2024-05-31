#include "bloqueEscenario.h"

bloqueEscenario::bloqueEscenario(const int32_t pos_x, const int32_t pos_y, const uint32_t ancho,
                                 const uint32_t alto, const int32_t angulo,
                                 const TipoBloqueEscenario tipo):
        pos_x(pos_x), pos_y(pos_y), ancho(ancho), alto(alto), angulo(angulo), tipo(tipo) {}
