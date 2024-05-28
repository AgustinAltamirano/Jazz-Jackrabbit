#include "personaje.h"

#include "../common/config.h"
#include "../common/constantes.h"

personaje::personaje(const int id, const int tipo, const int pos_x_inicial,
                     const int pos_y_inicial):
        id(id),
        tipo_de_personaje(tipo),
        alto(ALTO_INICIAL),
        ancho(ANCHO_INICIAL),
        pos_x(pos_x_inicial),
        vel_x(0),
        aceleracion_x(0),
        pos_y(pos_y_inicial),
        vel_y(0),
        angulo(0),
        sobre_rampa(false),
        de_espaldas(false),
        en_aire(false),
        ataque_especial(false),
        puntos(0) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    aceleracion_y = configurador.get(GRAVEDAD);
    vida = configurador.get(VIDA_INICIAL);
}

void personaje::cambiar_velocidad(const std::vector<std::string>& teclas) {
    if (ataque_especial) {
        return;
    }
    for (const std::string tecla&: teclas) {
        // verificar si el estado permite hacer acciones
        switch (tecla) {
            case TECLA_DERECHA:
                this->vel_x = 10;
                this->de_espaldas = false;
                break;
            case TECLA_IZQUIERDA:
                this->vel_y = -10;
                this->de_espaldas = true;
                break;
            default:
                break;
        }
    }
    this->vel_x += this->aceleracion_x;
    if (en_aire) {
        this->vel_y += this->aceleracion_y;
    }
}

void personaje::cambiar_posicion(const int x, const int y) {
    this->pos_x = x;
    this->pos_y = y;
}

std::vector<int> personaje::get_pos_actual() const {
    std::vector<int> pos_actual;
    pos_actual.push_back(pos_x);
    pos_actual.push_back(pos_y);
    return pos_actual;
}

std::vector<int> personaje::get_pos_a_ir() const {
    std::vector<int> pos_prox;
    if (sobre_rampa) {
        // esto solo contempla angulos de 45 grados (y 135)
        pos_prox.push_back(this->pos_x + this->vel_x * 707 / 1000);
        pos_prox.push_back(this->pos_y + this->vel_x * 707 / 1000);
        return pos_prox;
    } else {
        pos_prox.push_back(this->pos_x + this->vel_x);
    }
    if (en_aire) {
        pos_prox.push_back(this->pos_y + this->vel_y);
    } else {
        pos_prox.push_back(this->pos_y);
    }
    return pos_prox;
}

int personaje::get_alto() const { return alto; }

int personaje::get_ancho() const { return ancho; }
