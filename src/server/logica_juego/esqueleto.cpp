#include "esqueleto.h"

#include "../../common/config.h"
#include "../../common/constantes.h"

Esqueleto::Esqueleto(const int32_t id, const int32_t pos_x_in, const int32_t pos_y_in):
        id(id),
        pos_x(pos_x_in),
        pos_y(pos_y_in),
        ancho(ANCHO_ENEMIGO),
        alto(ALTURA_ENEMIGO),
        tipo(ESQUELETO),
        estado(ACTIVO),
        de_espaldas(true) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VELOCIDAD_ESQUELETO);
    this->dano = configurador.get(DANO_ESQUELETO);
    this->puntos = configurador.get(PUNTOS_ESQUELETO);
    this->vida = configurador.get(VIDA_ESQUELETO);
    this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_ESQ);
}

EstadoEnemigo Esqueleto::get_estado() const { return estado; }

int32_t Esqueleto::get_puntos() const { return puntos; }

bool Esqueleto::esta_invertido() const { return de_espaldas; }

void Esqueleto::mover() {
    if (this->estado != MUERTO) {
        this->pos_x += vel_x;
    } else {
        this->contador_estado_muerto -= 1;
        if (contador_estado_muerto <= 0) {
            this->revivir();
        }
    }
}

void Esqueleto::chocar_pared() {
    this->vel_x *= -1;
    this->de_espaldas = !this->de_espaldas;
}

int32_t Esqueleto::atacar() const { return dano; }

bool Esqueleto::hacer_dano(int32_t const puntos_dano) {
    this->vida -= puntos_dano;
    if (vida <= 0) {
        this->estado = MUERTO;
        return true;
    }
    return false;
}

void Esqueleto::revivir() {
    this->estado = ACTIVO;
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_ESQ);
    this->vida = configurador.get(VIDA_ESQUELETO);
}

EnemigoDTO Esqueleto::crear_dto() const {
    const EnemigoDTO enem(id, pos_x, pos_y, alto, ancho, tipo, de_espaldas);
    return enem;
}

int32_t Esqueleto::get_pos_x() { return pos_x; }

int32_t Esqueleto::get_pos_y() { return pos_y; }

int32_t Esqueleto::get_alto() { return ancho; }

int32_t Esqueleto::get_ancho() { return alto; }

void Esqueleto::chequear_colisiones(std::vector<bloqueEscenario>& bloques,
                                    std::vector<bloqueEscenario>& angulos) {
    if (estado == MUERTO) {
        return;
    }
    this->mover();
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
    const bool cae =
            !std::any_of(bloques.begin(), bloques.end(), [&](const bloqueEscenario& bloque) {
                return bloque.pos_y == pos_y + alto + 1 &&
                       colision_horizontal(pos_x, ancho, bloque);
            });
    if (cae) {
        this->chocar_pared();
        this->mover();
    }
}
