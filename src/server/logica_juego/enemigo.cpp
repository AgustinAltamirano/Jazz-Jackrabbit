#include "enemigo.h"

#include "../../common/config.h"
#include "../../common/constantes.h"

enemigo::enemigo(const int32_t id, const int32_t pos_x_in, const int32_t pos_y_in,
                 const TipoEnemigo tipo):
        id(id),
        pos_x(pos_x_in),
        pos_y(pos_y_in),
        ancho(ANCHO_ENEMIGO),
        alto(ALTURA_ENEMIGO),
        tipo(tipo),
        estado(ACTIVO),
        de_espaldas(true) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    switch (tipo) {
        case LAGARTO:
            this->vel_x = configurador.get(VELOCIDAD_LAGARTO);
            this->dano = configurador.get(DANO_LAGARTO);
            this->puntos = configurador.get(PUNTOS_LAGARTO);
            this->vida = configurador.get(VIDA_LAGARTO);
            this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_LAG);
            break;
        case MURCIELAGO:
            this->vel_x = configurador.get(VELOCIDAD_MURCIELAGO);
            this->dano = configurador.get(DANO_MURCIELAGO);
            this->puntos = configurador.get(PUNTOS_MURCIELAGO);
            this->vida = configurador.get(VIDA_MURCIELAGO);
            this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_MUR);
            break;
        case ESQUELETO:
            this->vel_x = configurador.get(VELOCIDAD_ESQUELETO);
            this->dano = configurador.get(DANO_ESQUELETO);
            this->puntos = configurador.get(PUNTOS_ESQUELETO);
            this->vida = configurador.get(VIDA_ESQUELETO);
            this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_ESQ);
            break;
        default:
            break;
    }
}

int32_t enemigo::get_prox_pos_x() const { return pos_x + vel_x; }

int32_t enemigo::get_pos_x() const { return pos_x; }

int32_t enemigo::get_pos_y() const { return pos_y; }

int32_t enemigo::get_alto() const { return alto; }

int32_t enemigo::get_ancho() const { return ancho; }

EstadoEnemigo enemigo::get_estado() const { return estado; }

int32_t enemigo::get_puntos() const { return puntos; }

bool enemigo::esta_invertido() const { return de_espaldas; }

void enemigo::mover() {
    if (this->estado != MUERTO) {
        this->pos_x += vel_x;
    } else {
        this->contador_estado_muerto -= 1;
        if (contador_estado_muerto <= 0) {
            this->revivir();
        }
    }
}

void enemigo::chocar_pared() {
    this->vel_x *= -1;
    this->de_espaldas = !this->de_espaldas;
}

int32_t enemigo::atacar() const { return dano; }

bool enemigo::hacer_dano(int32_t const puntos_dano) {
    this->vida -= puntos_dano;
    if (vida <= 0) {
        this->estado = MUERTO;
        return true;
    }
    return false;
}

void enemigo::revivir() {
    this->estado = ACTIVO;
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    switch (this->tipo) {
        case LAGARTO:
            this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_LAG);
            break;
        case MURCIELAGO:
            this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_MUR);
            break;
        case ESQUELETO:
            this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_ESQ);
            break;
    }
}
