#ifndef BALA_ARMA_2_H
#define BALA_ARMA_2_H

#include <vector>

#include "../../../common/config.h"
#include "../../../common/constantes.h"

#include "bala.h"

class balaArma2: public bala {
private:
    int32_t id_dueno;
    int32_t pos_x, pos_y;
    int32_t vel_x, vel_y;
    bool choco;
    uint32_t dano;
    uint32_t tiempo_recarga;  // frames hasta poder volver a disparar
public:
    balaArma2(int32_t id, int32_t pos_x_in, int32_t pos_y_in, bool invertido);
    [[nodiscard]] std::vector<int32_t> get_pos() const override;
    void mover() override;
    [[nodiscard]] uint32_t impactar() override;
    [[nodiscard]] int32_t get_id() const override;
    [[nodiscard]] uint32_t disparar() override;
};

#endif  // BALA_ARMA_2_H
