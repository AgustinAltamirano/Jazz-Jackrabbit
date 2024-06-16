#include "bala_arma_3.h"

balaArma3::balaArma3(const int32_t id, int32_t const pos_x_in, int32_t const pos_y_in,
                     bool const invertido):
        id_dueno(id), pos_x(pos_x_in), pos_y(pos_y_in), choco(false), tipo(ARMA3) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VEL_ARMA3);
    if (invertido) {
        this->vel_x *= -1;
    }
    this->dano = configurador.get(DANO_ARMA3);
    this->tiempo_recarga = configurador.get(FRAMES_REC_ARMA3);
}

std::vector<int32_t> balaArma3::get_pos() const {
    std::vector<int32_t> posicion;
    posicion.push_back(this->pos_x);
    posicion.push_back(this->pos_y);
    return posicion;
}

bool balaArma3::mover() {
    this->pos_x += this->vel_x;
    return this->choco;
}

int32_t balaArma3::impactar() {
    this->choco = true;
    return this->dano;
}

int32_t balaArma3::get_id() const { return this->id_dueno; }

int32_t balaArma3::disparar() {
    this->mover();
    return this->tiempo_recarga;
}

BalaDTO balaArma3::crear_dto() {
    const BalaDTO bala(pos_x, pos_y, tipo);
    return bala;
}
