#include "personaje.h"

#include "../../common/config.h"
#include "../../common/constantes.h"

personaje::personaje(const int32_t id, const TipoPersonaje tipo, const int32_t pos_x_inicial,
                     const int32_t pos_y_inicial):
        id(id),
        tipo_de_personaje(tipo),
        alto(ALTO_INICIAL),
        ancho(ANCHO_INICIAL),
        pos_x(pos_x_inicial),
        vel_x(0),
        aceleracion_x(0),
        pos_y(pos_y_inicial),
        vel_y(0),
        sobre_rampa(false),
        de_espaldas(false),
        en_aire(false),
        ataque_especial(false),
        estado(EstadoPersonaje::IDLE),
        tiempo_estado(0),
        puntos(0),
        arma_actual(INFINITA) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    aceleracion_y = configurador.get(GRAVEDAD);
    vida = configurador.get(VIDA_INICIAL);
}

void personaje::cambiar_velocidad(const std::vector<AccionJuego>& teclas) {
    if (ataque_especial || this->estado == MUERTE || this->estado == IMPACTADO) {
        return;
    }
    for (const AccionJuego tecla&: teclas) {
        // verificar si el estado permite hacer acciones
        switch (tecla) {
            case SALTAR:
                if (!en_aire && (this->estado != INTOXICADO)) {
                    this->vel_y = 12;
                    this->en_aire = true;
                }
            case MOVER_DER:
                this->vel_x = 2;
                this->de_espaldas = false;
            case MOVER_IZQ:
                this->vel_y = -2;
                this->de_espaldas = true;
            case ACTIVAR_DASH:
                // por hacer
                break;
            case DISPARAR_ACCION:
                if (this->estado != INTOXICADO) {
                    // disparar();
                    this->estado = DISPARAR_QUIETO;
                }
            case ARMA_ANTERIOR:
                if (this->arma_actual == INFINITA) {
                    this->arma_actual = ARMA3;
                } else {
                    this->arma_actual = static_cast<ArmaActual>(arma_actual - 1);
                }
            case ARMA_SIGUIENTE:
                if (this->arma_actual == ARMA3) {
                    this->arma_actual = INFINITA;
                } else {
                    this->arma_actual = static_cast<ArmaActual>(arma_actual + 1);
                }
            case ATAQUEESPECIAL:
                // por hacer
                ataque_especial = true;
                break;
            default:  // si no es ningun caso que conozco lo ignoro
                break;
        }
    }
    this->vel_x += this->aceleracion_x;
    if (en_aire) {
        this->vel_y += this->aceleracion_y;
    }
}

void personaje::cambiar_posicion(const uint32_t x, const uint32_t y) {
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
    }
    pos_prox.push_back(this->pos_x + this->vel_x);
    if (en_aire) {
        pos_prox.push_back(this->pos_y + this->vel_y);
    } else {
        pos_prox.push_back(this->pos_y);
    }
    return pos_prox;
}

uint32_t personaje::get_alto() const { return alto; }

uint32_t personaje::get_ancho() const { return ancho; }

void personaje::cambiar_estado(const bool cae) {
    this->en_aire = cae;
    if (estado == MUERTE || estado == IMPACTADO || estado == DISPARAR_QUIETO ||
        estado == ATAQUE_ESPECIAL || estado == INTOXICADO) {
        return;
    }
    if (cae) {
        if (this->vel_x != 0) {
            if (this->vel_y < 0) {
                this->estado = SALTAR_ADELANTE;
            } else {
                this->estado = CAER_ADELANTE;
            }
        } else {
            if (this->vel_y < 0) {
                this->estado = SALTAR_ARRIBA;
            } else {
                this->estado = CAER_ABAJO;
            }
        }
    } else {
        if (this->vel_x != 0) {
            this->estado = CORRER;
        } else {
            this->estado = IDLE;
        }
    }
}

void personaje::pasar_tick() {
    this->tiempo_estado += 1;
    switch (estado) {
        case INTOXICADO:
            if (tiempo_estado == FRAMES_POR_SEGUNDO * 3) {
                this->estado = IDLE;
            }
        case MUERTE:
            if (tiempo_estado == FRAMES_POR_SEGUNDO * 5) {
                const ConfigAdmin& configurador = ConfigAdmin::getInstance();
                this->estado = IDLE;
                this->vida = configurador.get(VIDA_INICIAL);
            }
        case IMPACTADO:
            if (tiempo_estado == FRAMES_POR_SEGUNDO) {
                this->estado = IDLE;
            }
        case ATAQUE_ESPECIAL:
            return;
            // aca tengo que procesar cada caso individual
        default:
            this->estado = IDLE;
            this->tiempo_estado = 0;
    }
}
