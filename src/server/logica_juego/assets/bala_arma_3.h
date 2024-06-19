#ifndef BALA_ARMA_3_H
#define BALA_ARMA_3_H

#include <vector>

#include "../../../common/config.h"
#include "../../../common/constantes.h"
#include "../../../common/snapshot_dto.h"
#include "../../../common/tipo_arma.h"

#include "bala.h"

class balaArma3: public bala {
private:
    int32_t id_dueno;
    int32_t pos_x, pos_y;
    int32_t vel_x;
    bool choco;
    int32_t dano;
    int32_t tiempo_recarga;  // frames hasta poder volver a disparar
    const TipoArma tipo;

public:
    balaArma3(int32_t id, int32_t pos_x_in, int32_t pos_y_in, bool invertido);
    [[nodiscard]] std::vector<int32_t> get_pos() const override;
    bool mover() override;
    int32_t impactar() override;
    [[nodiscard]] int32_t get_id() const override;
    [[nodiscard]] int32_t disparar() override;
    [[nodiscard]] BalaDTO crear_dto() override;
};

#endif  // BALA_ARMA_3_H
