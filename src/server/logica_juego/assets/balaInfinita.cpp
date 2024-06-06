#include "balaInfinita.h"

balaInfinita::balaInfinita(const int32_t id, int32_t const pos_x_in, int32_t const pos_y_in,
                           bool const invertido):
        id_dueno(id), pos_x(pos_x_in), pos_y(pos_y_in), choco(false) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VEL_ARMA_INF);
    if (invertido) {
        this->vel_x *= -1;
    }
    this->dano = configurador.get(DANO_ARMA_INF);
    this->tiempo_recarga = configurador.get(FRAMES_REC_ARMA_INF);
}

std::vector<int32_t> balaInfinita::get_pos() const {
    std::vector<int32_t> posicion;
    posicion.push_back(this->pos_x);
    posicion.push_back(this->pos_y);
    return posicion;
}

void balaInfinita::mover() { this->pos_x += this->vel_x; }

uint32_t balaInfinita::impactar() {
    this->choco = true;
    return this->dano;
}

int32_t balaInfinita::get_id() const { return this->id_dueno; }

uint32_t balaInfinita::disparar() {
    this->mover();
    return this->tiempo_recarga;
}
