#include "murcielago.h"

#include "../../common/config.h"
#include "../../common/constantes.h"

Murcielago::Murcielago(const int32_t id, const int32_t pos_x_in, const int32_t pos_y_in):
        id(id),
        pos_x(pos_x_in),
        pos_y(pos_y_in),
        ancho(ANCHO_ENEMIGO),
        alto(ALTURA_ENEMIGO),
        tipo(MURCIELAGO),
        estado(ACTIVO),
        de_espaldas(true) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VELOCIDAD_MURCIELAGO);
    this->dano = configurador.get(DANO_MURCIELAGO);
    this->puntos = configurador.get(PUNTOS_MURCIELAGO);
    this->vida = configurador.get(VIDA_MURCIELAGO);
    this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_MUR);
}

EstadoEnemigo Murcielago::get_estado() const { return estado; }

int32_t Murcielago::get_puntos() const { return puntos; }

bool Murcielago::esta_invertido() const { return de_espaldas; }

void Murcielago::mover() {
    if (this->estado != MUERTO) {
        this->pos_x += vel_x;
    } else {
        this->contador_estado_muerto -= 1;
        if (contador_estado_muerto <= 0) {
            this->revivir();
        }
    }
}

void Murcielago::chocar_pared() {
    this->vel_x *= -1;
    this->de_espaldas = !this->de_espaldas;
}

int32_t Murcielago::atacar() const { return dano; }

bool Murcielago::hacer_dano(int32_t const puntos_dano) {
    this->vida -= puntos_dano;
    if (vida <= 0) {
        this->estado = MUERTO;
        return true;
    }
    return false;
}

void Murcielago::revivir() {
    this->estado = ACTIVO;
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_MUR);
    this->vida = configurador.get(VIDA_MURCIELAGO);
}

EnemigoDTO Murcielago::crear_dto() const {
    const EnemigoDTO enem(id, pos_x, pos_y, alto, ancho, tipo, de_espaldas);
    return enem;
}

int32_t Murcielago::get_pos_x() { return pos_x; }

int32_t Murcielago::get_pos_y() { return pos_y; }

int32_t Murcielago::get_alto() { return ancho; }

int32_t Murcielago::get_ancho() { return alto; }

void Murcielago::chequear_colisiones(std::vector<bloqueEscenario>& bloques,
                                     std::vector<bloqueEscenario>& angulos) {
    this->mover();
    if (estado == MUERTO) {
        return;
    }
    for (const auto& bloque: bloques) {
        if (pos_x < bloque.pos_x + bloque.ancho && pos_x + ancho > bloque.pos_x &&
            pos_y < bloque.pos_y + bloque.alto && pos_y + alto > bloque.pos_y) {
            this->chocar_pared();
            this->mover();
        }
    }
    for (const auto& bloque: angulos) {
        if (pos_x < bloque.pos_x + bloque.ancho && pos_x + ancho > bloque.pos_x &&
            pos_y < bloque.pos_y + bloque.alto && pos_y + alto > bloque.pos_y) {
            this->chocar_pared();
            this->mover();
        }
    }
}
