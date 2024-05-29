#ifndef BLOQUEESCENARIO_H
#define BLOQUEESCENARIO_H

typedef enum {
    PISO = 0,
    TECHO,
    PARED,
    DIAGONAL,
} TipoBloqueEscenario;

class bloqueEscenario {
public:
    int pos_x;
    int pos_y;
    int ancho;
    int alto;
    int angulo;
    TipoBloqueEscenario tipo;
    bloqueEscenario(int pos_x, int pos_y, int ancho, int alto, int angulo,
                    TipoBloqueEscenario tipo);
};

#endif  // BLOQUEESCENARIO_H
