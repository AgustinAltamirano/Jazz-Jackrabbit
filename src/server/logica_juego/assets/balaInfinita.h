#ifndef BALAINFINITA_H
#define BALAINFINITA_H

#include <vector>

#include "../../../common/config.h"

#include "bala.h"

class balaInfinita: public bala {
private:
    int32_t pos_x, pos_y;
    int32_t vel_x;
    bool choco;
    uint32_t dano;
    uint32_t tiempo_recarga;  // tiempo que tiene el personaje antes de poder disparar una bala otra
                              // vez
public:
    balaInfinita(int32_t pos_x_in, int32_t pos_y_in, bool invertido);
    std::vector<int32_t> get_pos() override;
    void update() override;
    void impactar() override;
};


#endif  // BALAINFINITA_H
