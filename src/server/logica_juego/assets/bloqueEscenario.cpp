#include "bloqueEscenario.h"

bloqueEscenario::bloqueEscenario(const int pos_x, const int pos_y, const int ancho, const int alto,
                                 const int angulo, const TipoBloqueEscenario tipo):
        pos_x(pos_x), pos_y(pos_y), ancho(ancho), alto(alto), angulo(angulo), tipo(tipo) {}
