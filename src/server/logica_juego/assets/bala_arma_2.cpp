#include "bala_arma_2.h"

balaArma2::balaArma2(const int32_t id, int32_t const pos_x_in, int32_t const pos_y_in,
                     bool const invertido):
        id_dueno(id), pos_x(pos_x_in), pos_y(pos_y_in), choco(false) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VEL_ARMA2);
    if (invertido) {
        this->vel_x *= -1;
    }
    this->vel_y = configurador.get(CAIDA_ARMA2);
    this->dano = configurador.get(DANO_ARMA2);
    this->tiempo_recarga = configurador.get(FRAMES_REC_ARMA2);
}

std::vector<int32_t> balaArma2::get_pos() const {
    std::vector<int32_t> posicion;
    posicion.push_back(this->pos_x);
    posicion.push_back(this->pos_y);
    return posicion;
}

void balaArma2::mover() {
    this->pos_x += this->vel_x;
    this->pos_y += this->vel_y;
}

uint32_t balaArma2::impactar() {
    this->choco = true;
    return this->dano;
}

int32_t balaArma2::get_id() const { return this->id_dueno; }

uint32_t balaArma2::disparar() {
    this->mover();
    return this->tiempo_recarga;
}
