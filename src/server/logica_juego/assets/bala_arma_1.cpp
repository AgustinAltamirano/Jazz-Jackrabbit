#include "bala_arma_1.h"

balaArma1::balaArma1(const int32_t id, int32_t const pos_x_in, int32_t const pos_y_in,
                     bool const invertido):
        id_dueno(id), pos_x(pos_x_in), pos_y(pos_y_in), choco(false), rebotes(0) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VEL_ARMA1);
    if (invertido) {
        this->vel_x *= -1;
    }
    this->dano = configurador.get(DANO_ARMA1);
    this->tiempo_recarga = configurador.get(FRAMES_REC_ARMA1);
}

std::vector<int32_t> balaArma1::get_pos() const {
    std::vector<int32_t> posicion;
    posicion.push_back(this->pos_x);
    posicion.push_back(this->pos_y);
    return posicion;
}

bool balaArma1::mover() {
    this->pos_x += this->vel_x;
    return this->choco;
}

int32_t balaArma1::impactar() {
    rebotes += 1;
    if (rebotes >= 3) {
        this->choco = true;
    } else {
        this->vel_x *= -1;
    }
    return this->dano;
}

int32_t balaArma1::get_id() const { return this->id_dueno; }

int32_t balaArma1::disparar() {
    this->mover();
    return this->tiempo_recarga;
}
