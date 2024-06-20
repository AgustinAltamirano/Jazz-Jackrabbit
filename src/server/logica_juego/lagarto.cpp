#include "lagarto.h"

#include "../../common/config.h"
#include "../../common/constantes.h"

Lagarto::Lagarto(const int32_t id, const int32_t pos_x_in, const int32_t pos_y_in):
        id(id),
        pos_x(pos_x_in),
        pos_y(pos_y_in),
        ancho(ANCHO_ENEMIGO),
        alto(ALTURA_ENEMIGO),
        tipo(LAGARTO),
        estado(ACTIVO),
        de_espaldas(false) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->vel_x = configurador.get(VELOCIDAD_LAGARTO);
    this->dano = configurador.get(DANO_LAGARTO);
    this->puntos = configurador.get(PUNTOS_LAGARTO);
    this->vida = configurador.get(VIDA_LAGARTO);
    this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_LAG);
}

EstadoEnemigo Lagarto::get_estado() const { return estado; }

int32_t Lagarto::get_puntos() const { return puntos; }

bool Lagarto::esta_invertido() const { return de_espaldas; }

void Lagarto::mover() {
    if (this->estado != MUERTO) {
        this->pos_x += vel_x;
    } else {
        this->contador_estado_muerto -= 1;
        if (contador_estado_muerto <= 0) {
            this->revivir();
        }
    }
}

void Lagarto::chocar_pared() {
    this->vel_x *= -1;
    this->de_espaldas = !this->de_espaldas;
}

int32_t Lagarto::atacar() const { return dano; }

bool Lagarto::hacer_dano(int32_t const puntos_dano) {
    this->vida -= puntos_dano;
    if (vida <= 0) {
        this->estado = MUERTO;
        return true;
    }
    return false;
}

void Lagarto::revivir() {
    this->estado = ACTIVO;
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    this->contador_estado_muerto = configurador.get(FRAMES_REVIVIR_LAG);
    this->vida = configurador.get(VIDA_LAGARTO);
}

EnemigoDTO Lagarto::crear_dto() const {
    const EnemigoDTO enem(id, pos_x, pos_y, alto, ancho, tipo, de_espaldas);
    return enem;
}

int32_t Lagarto::get_pos_x() { return pos_x; }

int32_t Lagarto::get_pos_y() { return pos_y; }

int32_t Lagarto::get_alto() { return ancho; }

int32_t Lagarto::get_ancho() { return alto; }

void Lagarto::chequear_colisiones(std::vector<bloqueEscenario>& bloques,
                                  std::vector<bloqueEscenario>& angulos) {
    this->mover();
    if (estado == MUERTO) {
        return;
    }
    for (const auto& bloque: bloques) {
        if (pos_x < bloque.pos_x + bloque.ancho && pos_x + ancho > bloque.pos_x &&
            pos_y < bloque.pos_y + bloque.alto && pos_y + alto > bloque.pos_y) {
            this->chocar_pared();
        }
    }
    for (const auto& bloque: angulos) {
        if (pos_x < bloque.pos_x + bloque.ancho && pos_x + ancho > bloque.pos_x &&
            pos_y < bloque.pos_y + bloque.alto && pos_y + alto > bloque.pos_y) {
            this->chocar_pared();
        }
    }
    const bool cae =
            !std::any_of(bloques.begin(), bloques.end(), [&](const bloqueEscenario& bloque) {
                return bloque.pos_y == pos_y + alto + 1 &&
                       colision_horizontal(pos_x, ancho, bloque);
            });
    if (cae) {
        this->chocar_pared();
    }
}

void Lagarto::matar() {
    this->vida = 0;
    this->estado = MUERTO;
}
