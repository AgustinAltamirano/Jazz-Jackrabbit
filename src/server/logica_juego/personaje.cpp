#include "personaje.h"

#include "../../common/config.h"
#include "../../common/constantes.h"

personaje::personaje(const int32_t id, const TipoPersonaje tipo, const int32_t pos_x_inicial,
                     const int32_t pos_y_inicial):
        spawn_x(pos_x_inicial),
        spawn_y(pos_y_inicial),
        id(id),
        tipo_de_personaje(tipo),
        alto(ALTO_INICIAL),
        ancho(ANCHO_INICIAL),
        pos_x(pos_x_inicial),
        vel_x(0),
        mover_izq(false),
        mover_der(false),
        pos_y(pos_y_inicial),
        vel_y(0),
        dash(false),
        de_espaldas(false),
        en_aire(false),
        ataque_especial(false),
        estado(EstadoPersonaje::IDLE),
        tiempo_estado(0),
        puntos(0),
        arma_actual(INFINITA),
        tiempo_recarga(0) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    aceleracion_y = configurador.get(GRAVEDAD);
    vida = configurador.get(VIDA_INICIAL);
    inventario_balas[INFINITA] = -1;
    inventario_balas[ARMA1] = 0;
    inventario_balas[ARMA2] = 0;
    inventario_balas[ARMA3] = 0;
}

bool personaje::ejecutar_accion(const std::vector<TipoComando>& teclas) {
    if (ataque_especial || this->estado == MUERTE) {
        return false;
    }
    bool disparo = false;
    for (const TipoComando& tecla: teclas) {
        // verificar si el estado permite hacer acciones
        switch (tecla) {
            case SALTAR:
                if (!en_aire && (this->estado != INTOXICADO) && (this->estado != IMPACTADO)) {
                    this->vel_y = -16;
                    this->en_aire = true;
                }
                break;
            case MOVER_DER:
                this->mover_der = true;
                this->mover_izq = false;
                break;
            case PARAR_MOVER_DER:
                this->mover_der = false;
                break;
            case MOVER_IZQ:
                this->mover_izq = true;
                this->mover_der = false;
                break;
            case PARAR_MOVER_IZQ:
                this->mover_izq = false;
                break;
            case ACTIVAR_DASH:
                if (!en_aire && (this->estado != INTOXICADO) && (this->estado != IMPACTADO)) {
                    this->dash = true;
                }
                break;
            case DESACTIVAR_DASH:
                this->dash = false;
                break;
            case DISPARAR_ACCION:
                if (this->estado != INTOXICADO && this->estado != INTOXICADO_MOVIMIENTO &&
                    this->tiempo_recarga == 0 && inventario_balas[arma_actual] != 0 &&
                    this->estado != IMPACTADO) {
                    this->estado = DISPARAR_QUIETO;
                    disparo = true;
                }
                break;
            case ARMA_ANTERIOR:
                if (this->arma_actual == INFINITA) {
                    this->arma_actual = ARMA3;
                } else {
                    this->arma_actual = static_cast<TipoArma>(arma_actual - 1);
                }
                break;
            case ARMA_SIGUIENTE:
                if (this->arma_actual == ARMA3) {
                    this->arma_actual = INFINITA;
                } else {
                    this->arma_actual = static_cast<TipoArma>(arma_actual + 1);
                }
                break;
            case ACTIVAR_ATAQUE_ESPECIAL:
                switch (tipo_de_personaje) {
                    case JAZZ:
                        if (!en_aire && (this->estado != INTOXICADO) &&
                            (this->estado != IMPACTADO)) {
                            this->vel_y = -24;
                            this->en_aire = true;
                            this->ataque_especial = true;
                        }
                        break;
                    case LORI:
                        if (en_aire && (this->estado != INTOXICADO) &&
                            (this->estado != IMPACTADO)) {
                            this->ataque_especial = true;
                        }
                        break;
                    case SPAZ:
                        if (!en_aire && (this->estado != INTOXICADO) &&
                            (this->estado != IMPACTADO)) {
                            this->vel_x = 10;
                            this->ataque_especial = true;
                            if (de_espaldas) {
                                this->vel_x *= -1;
                            }
                        }
                        break;
                    default:
                        break;
                }
            case TRUCO1:
                // aca agrego balas de arma a todas las armas del personaje
                inventario_balas[ARMA1] += 20;
                inventario_balas[ARMA2] += 20;
                inventario_balas[ARMA3] += 20;
                break;
            case TRUCO2:  // matar todos los enemigos
            case TRUCO3:  // termina la partida, es irrelevante que el jugador lo procese
            default:      // si no es ningun caso que conozco lo ignoro
                break;
        }
    }
    if (mover_der) {
        this->vel_x = 5;
        if (dash) {
            this->vel_x *= 2;
        }
        this->de_espaldas = false;
    } else if (mover_izq) {
        this->vel_x = -5;
        if (dash) {
            this->vel_x *= 2;
        }
        this->de_espaldas = true;
    }
    return disparo;
}

void personaje::efectuar_gravedad() {
    if (en_aire) {
        this->vel_y += this->aceleracion_y;
    }
}

void personaje::dejar_de_caer() {
    this->en_aire = false;
    this->vel_y = 0;  // hago reset a la velocidad para reducir riesgos de bugs
}


void personaje::cambiar_posicion(const int32_t x, const int32_t y) {
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
    pos_prox.push_back(this->pos_x + this->vel_x);
    if (en_aire) {
        pos_prox.push_back(this->pos_y + this->vel_y);
    } else {
        pos_prox.push_back(this->pos_y);
    }
    return pos_prox;
}

int32_t personaje::get_alto() const { return alto; }

int32_t personaje::get_ancho() const { return ancho; }

void personaje::cambiar_estado(const bool cae) {
    this->en_aire = cae;
    if (estado == MUERTE || estado == IMPACTADO) {
        this->vel_x = 0;  // reseteo la velocidad
        return;
    }
    if (ataque_especial) {
        this->estado = ATAQUE_ESPECIAL;
        if (this->tipo_de_personaje == LORI) {
            this->dejar_de_caer();
        }
        return;
    }
    if (estado == INTOXICADO || estado == INTOXICADO_MOVIMIENTO) {
        if (vel_x != 0) {
            this->estado = INTOXICADO_MOVIMIENTO;
        } else {
            this->estado = INTOXICADO;
        }
    } else if (tiempo_recarga > 0 && vel_x == 0) {
        this->estado = DISPARAR_QUIETO;
    } else if (cae) {
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
            if (dash) {
                this->estado = DASH;
            } else {
                this->estado = CORRER;
            }
        } else {
            this->estado = IDLE;
        }
    }
    if (!en_aire) {
        if (this->vel_x > 0) {
            this->vel_x -= 1;
            if (this->vel_x <= 0) {
                this->vel_x = 0;
                this->dash = false;
            }
        } else if (this->vel_x < 0) {
            this->vel_x += 1;
            if (this->vel_x >= 0) {
                this->vel_x = 0;
                this->dash = false;
            }
        }
    }
}

void personaje::pasar_tick() {
    this->tiempo_estado += 1;
    if (this->tiempo_recarga != 0) {
        this->tiempo_recarga -= 1;
    }
    switch (estado) {
        case INTOXICADO:
        case INTOXICADO_MOVIMIENTO:
            if (tiempo_estado >= FRAMES_POR_SEGUNDO * 9) {
                this->estado = IDLE;
            }
            break;
        case MUERTE:
            if (tiempo_estado >= FRAMES_POR_SEGUNDO * 5) {
                const ConfigAdmin& configurador = ConfigAdmin::getInstance();
                this->estado = IDLE;
                this->vida = configurador.get(VIDA_INICIAL);
                this->pos_x = spawn_x;
                this->pos_y = spawn_y;
            }
            break;
        case IMPACTADO:
            if (tiempo_estado >= FRAMES_POR_SEGUNDO * 3 / 2) {
                this->estado = IDLE;
            }
            break;
        case ATAQUE_ESPECIAL:
            if (tiempo_estado >= FRAMES_POR_SEGUNDO) {
                this->estado = IDLE;
                ataque_especial = false;
            }
            break;
        default:
            this->estado = IDLE;
            this->tiempo_estado = 0;
    }
}

void personaje::recoger_objeto(const int32_t valor, const TipoRecogible tipo) {
    switch (tipo) {
        case GEMA_AGARRABLE:
        case MONEDA_AGARRABLE:
            this->puntos += valor;
            break;
        case MUNICION_ARMA_1:
            this->inventario_balas[ARMA1] += valor;
            break;
        case MUNICION_ARMA_2:
            this->inventario_balas[ARMA2] += valor;
            break;
        case MUNICION_ARMA_3:
            this->inventario_balas[ARMA3] += valor;
            break;
        case FRUTA_BUENA:
            this->vida += valor;
            break;
        case FRUTA_PODRIDA:
            if (this->vida > valor) {
                this->vida -= valor;
            }
            this->estado = INTOXICADO;
            break;
        default:
            break;
    }
}

TipoArma personaje::get_arma() const { return this->arma_actual; }

bool personaje::get_invertido() const { return this->de_espaldas; }

void personaje::disparar(const int32_t frames_recarga) {
    this->tiempo_recarga = frames_recarga;
    if (inventario_balas.at(arma_actual) != -1) {
        inventario_balas[arma_actual] -= 1;
    }
}

int personaje::efectuar_dano(int32_t const dano) {
    if (this->estado != IMPACTADO && this->estado != MUERTE && !ataque_especial) {
        this->vida -= dano;
        if (vida <= 0) {
            this->vida = 0;
            this->estado = MUERTE;
            return 2;
        }
        this->estado = IMPACTADO;
        return 1;
    }
    return 0;
}

void personaje::dar_puntos(int32_t const puntos) { this->puntos += puntos; }

ClienteDTO personaje::crear_dto() const {
    const int32_t balas_restantes = inventario_balas.at(arma_actual);
    const ClienteDTO jugador(id, tipo_de_personaje, pos_x, pos_y, de_espaldas, estado, vida, puntos,
                             arma_actual, balas_restantes);
    return jugador;
}

bool personaje::en_ataque_especial() const { return ataque_especial; }
