#ifndef COORDENADA_PUNTO_H
#define COORDENADA_PUNTO_H


class CoordenadaPunto {
public:
    CoordenadaPunto(qreal x, qreal y) : x(x), y(y) {}

    bool operator<(const CoordenadaPunto& otro) const {
        if (y != otro.y) {
            return y < otro.y;
        }
        return x < otro.x;
    }

    qreal x, y;
};

#endif  // COORDENADA_PUNTO_H
