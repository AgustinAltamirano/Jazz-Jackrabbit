#include "manejadorEscenario.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <utility>

#include <yaml-cpp/yaml.h>

#include "../../common/constantes.h"
#include "../../common/snapshot_dto.h"
#include "../../common/tipo_bloque_escenario.h"

manejadorEscenario::manejadorEscenario(std::string path):
        path(std::move(path)), clase_escenario(ESCENARIO_INDEFINIDO) {
    this->cargar_escenario();
    this->cargar_enemigos();
}

void manejadorEscenario::cargar_escenario() {
    YAML::Node archivo = YAML::LoadFile(MAPAS_PATH + this->path + ".yaml");
    // para calcular los bordes del mapa
    int32_t ancho_mapa = 0;
    int32_t alto_mapa = 0;
    // cargo el tipo de escenario
    this->clase_escenario = static_cast<TipoEscenario>(archivo["items"][0]["escenario"].as<int>());
    // ahora cargo los bloques
    const YAML::Node& nodo_bloques = archivo["items"][1]["bloques"];
    for (const auto& nodo_bloque: nodo_bloques) {
        auto tipo = static_cast<TipoBloqueEscenario>(nodo_bloque["tipo"].as<int>());
        auto pos_x = nodo_bloque["x"].as<int>();
        auto pos_y = nodo_bloque["y"].as<int>();
        if (pos_x > ancho_mapa) {
            ancho_mapa = pos_x;
        }
        if (pos_y > alto_mapa) {
            alto_mapa = pos_y;
        }
        switch (tipo) {
            case PISO:
            case PARED:
            case SOPORTE_DIAGONAL:
            case SOPORTE_DIAGONAL_INVERTIDO:
                bloques_rectos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, 0, tipo);
                break;
            case DIAGONAL:
            case DIAGONAL_INVERTIDO:
                bloques_angulados.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, 0, tipo);
                break;
            case SPAWNPOINT_JUGADOR:
                spawnpoints.emplace_back(pos_x, pos_y);
                break;
            case SPAWNPOINT_ENEMIGO:
                spawnpoints_enemigos.emplace_back(pos_x, pos_y);
                break;
            case GEMA:
                objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, GEMA_AGARRABLE);
                break;
            case MONEDA:
                objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, MONEDA_AGARRABLE);
                break;
            default:
                continue;
        }
    }
}

int enemigo_aleatorio(const int semilla) {
    std::srand(semilla * 100);
    return std::rand() % 3;
}

void manejadorEscenario::cargar_enemigos() {
    int32_t id = 0;
    for (auto& spawn: spawnpoints_enemigos) {
        switch (enemigo_aleatorio(id)) {
            case 0:  // creo un lagarto
                enemigos.emplace_back(id, spawn.pos_x, spawn.pos_y, LAGARTO);
                break;
            case 1:  // creo un esqueleto
                enemigos.emplace_back(id, spawn.pos_x, spawn.pos_y, ESQUELETO);
                break;
            case 2:   // creo un murcielago
            default:  // si el generador de numeros falla, creo un murcielago
                enemigos.emplace_back(id, spawn.pos_x, spawn.pos_y, MURCIELAGO);
                break;
        }
        ++id;
    }
}

std::vector<spawnpoint>& manejadorEscenario::get_spawns() { return spawnpoints; }

TipoEscenario manejadorEscenario::get_escenario() { return clase_escenario; }

bool hay_colision_recta(const int32_t jug_x, const int32_t jug_y, const int32_t alto,
                        const int32_t ancho, const bloqueEscenario& bloque) {
    return (jug_x < bloque.pos_x + bloque.ancho && jug_x + ancho > bloque.pos_x &&
            jug_y < bloque.pos_y + bloque.alto && jug_y + alto > bloque.pos_y);
}

bool hay_colision_enemigo(const int32_t jug_x, const int32_t jug_y, const int32_t alto,
                          const int32_t ancho, const enemigo& enemigo) {
    return (jug_x < enemigo.get_pos_x() + enemigo.get_ancho() &&
            jug_x + ancho > enemigo.get_pos_x() &&
            jug_y < enemigo.get_pos_y() + enemigo.get_alto() && jug_y + alto > enemigo.get_pos_y());
}

std::vector<bloqueEscenario> chequeo_recto_individual(const personaje& jugador,
                                                      const std::vector<bloqueEscenario>& bloques) {
    std::vector<bloqueEscenario> colisiones;
    const std::vector<int> posicion_prox = jugador.get_pos_a_ir();
    int32_t jug_x = posicion_prox[0];
    int32_t jug_y = posicion_prox[1];
    colisiones.reserve(bloques.size());
    std::copy_if(bloques.begin(), bloques.end(), std::back_inserter(colisiones),
                 [&](const bloqueEscenario& bloque) {
                     return hay_colision_recta(jug_x, jug_y, jugador.get_alto(),
                                               jugador.get_ancho(), bloque);
                 });
    return colisiones;
}

int32_t definir_punto_medio(const int32_t pos_org_jug, const int32_t jug_largo,
                            const int32_t pos_bloque, const int32_t bloque_largo) {
    if (pos_org_jug < pos_bloque) {  // si este es el caso ajusto por arriba o por izquierda
        return (pos_bloque - jug_largo - 1);
    }
    return (pos_bloque + bloque_largo + 1);
}

bool colision_horizontal(const int32_t jug_x, const int32_t jug_ancho,
                         const bloqueEscenario& bloque) {
    return ((jug_x + jug_ancho > bloque.pos_x && jug_x < bloque.pos_x) ||
            (jug_x < bloque.pos_x + bloque.ancho &&
             jug_x + jug_ancho > bloque.pos_x + bloque.ancho));
}

void manejadorEscenario::colisiones_bloques_rectos(std::map<int, personaje>& jugadores) const {
    for (auto& entidad: jugadores) {
        personaje& jugador = entidad.second;
        std::vector<bloqueEscenario> colisiones = chequeo_recto_individual(jugador, bloques_rectos);

        std::vector<int> posicion_act = jugador.get_pos_actual();
        std::vector<int> posicion_prox = jugador.get_pos_a_ir();
        int32_t pos_x_jug_act = posicion_act[0], pos_y_jug_act = posicion_act[1];
        int32_t pos_x_jug_prox = posicion_prox[0], pos_y_jug_prox = posicion_prox[1];
        int32_t nueva_pos_x = pos_x_jug_prox, nueva_pos_y = pos_y_jug_prox;
        for (const auto& bloque: colisiones) {
            const int32_t inter_x =
                    std::min(pos_x_jug_prox + jugador.get_ancho(), bloque.pos_x + bloque.ancho) -
                    std::max(pos_x_jug_prox, bloque.pos_x);
            const int32_t inter_y =
                    std::min(pos_y_jug_prox + jugador.get_alto(), bloque.pos_y + bloque.alto) -
                    std::max(pos_y_jug_prox, bloque.pos_y);
            if (inter_x > inter_y) {
                nueva_pos_y = definir_punto_medio(pos_y_jug_act, jugador.get_alto(), bloque.pos_y,
                                                  bloque.alto);
                jugador.dejar_de_caer();
            } else {
                nueva_pos_x = definir_punto_medio(pos_x_jug_act, jugador.get_ancho(), bloque.pos_x,
                                                  bloque.ancho);
            }
        }
        jugador.cambiar_posicion(nueva_pos_x, nueva_pos_y);
        for (const auto& enemigo: enemigos) {
            if (hay_colision_enemigo(nueva_pos_x, nueva_pos_y, jugador.get_alto(),
                                     jugador.get_ancho(), enemigo)) {
                int32_t dano = enemigo.atacar();
                jugador.efectuar_dano(dano);
            }
        }
    }
}

void manejadorEscenario::hacer_tick_enemigos() {
    for (auto& en: enemigos) {
        int32_t prox_pos_x = en.get_prox_pos_x();
        int32_t pos_y = en.get_pos_y();
        int32_t ancho = en.get_ancho();
        int32_t alto = en.get_alto();
        for (const auto& bloque: bloques_rectos) {
            if (hay_colision_recta(prox_pos_x, pos_y, alto, ancho, bloque)) {
                en.chocar_pared();
            }
        }
        const bool caeria = !std::any_of(bloques_rectos.begin(), bloques_rectos.end(),
                                         [&](const bloqueEscenario& bloque) {
                                             return bloque.pos_y == (pos_y + alto + 1) &&
                                                    colision_horizontal(prox_pos_x, ancho, bloque);
                                         });
        if (caeria) {
            en.chocar_pared();
        }
        en.mover();
    }
}

void manejadorEscenario::colisiones_bloques_angulo(std::map<int, personaje>& jugadores) const {}


void manejadorEscenario::chequear_caida_y_objetos(std::map<int, personaje>& jugadores) {
    for (auto& entidad: jugadores) {
        personaje& jugador = entidad.second;
        const std::vector<int32_t> posicion = jugador.get_pos_actual();
        const int32_t punto_x = posicion[0];
        const int32_t punto_y = posicion[1];
        const int32_t punto_y_pisando = punto_y + jugador.get_alto() + 1;
        const bool cae = !std::any_of(
                bloques_rectos.begin(), bloques_rectos.end(), [&](const bloqueEscenario& bloque) {
                    return bloque.pos_y == punto_y_pisando &&
                           colision_horizontal(punto_x, jugador.get_ancho(), bloque);
                });
        jugador.cambiar_estado(cae);
        for (auto it = objetos.begin(); it != objetos.end();) {
            int32_t valor = (*it).chequear_colision(punto_x, punto_y, jugador.get_ancho(),
                                                    jugador.get_alto());
            if (valor != 0) {
                jugador.recoger_objeto(valor, (*it).get_objeto());
                it = objetos.erase(it);
            }
        }
    }
}


// seccion de creacion de snapshots
std::shared_ptr<SnapshotDTO> manejadorEscenario::crear_snapshot() {
    auto snapshot = std::make_shared<SnapshotDTO>(clase_escenario);
    for (const auto& bloque: bloques_rectos) {
        BloqueEscenarioDTO bloque_escenario_dto(bloque.pos_x, bloque.pos_y, bloque.ancho,
                                                bloque.alto, bloque.angulo, bloque.tipo);
        snapshot->agregar_bloque_escenario(std::move(bloque_escenario_dto));
    }
    for (const auto& bloque: bloques_angulados) {
        BloqueEscenarioDTO bloque_escenario_dto(bloque.pos_x, bloque.pos_y, bloque.ancho,
                                                bloque.alto, bloque.angulo, bloque.tipo);
        snapshot->agregar_bloque_escenario(std::move(bloque_escenario_dto));
    }
    return snapshot;
}

void manejadorEscenario::jugador_dispara(int32_t id, personaje& jugador) {
    const std::vector<int32_t> posicion = jugador.get_pos_actual();
    int32_t punto_x = posicion[0];
    if (!jugador.get_invertido()) {
        punto_x += jugador.get_ancho();
    }
    int32_t punto_y = posicion[1] + jugador.get_alto() / 2;

    switch (jugador.get_arma()) {
        case INFINITA: {
            std::unique_ptr<bala> balaI =
                    std::make_unique<balaInfinita>(id, punto_x, punto_y, jugador.get_invertido());
            jugador.disparar(balaI->disparar());
            balas.push_back(std::move(balaI));
            break;
        }
        case ARMA1: {
            std::unique_ptr<bala> bala1 =
                    std::make_unique<balaArma1>(id, punto_x, punto_y, jugador.get_invertido());
            jugador.disparar(bala1->disparar());
            balas.push_back(std::move(bala1));
            break;
        }
        case ARMA2: {
            std::unique_ptr<bala> bala2 =
                    std::make_unique<balaArma2>(id, punto_x, punto_y, jugador.get_invertido());
            jugador.disparar(bala2->disparar());
            balas.push_back(std::move(bala2));
            break;
        }
        case ARMA3: {
            std::unique_ptr<bala> bala3 =
                    std::make_unique<balaArma3>(id, punto_x, punto_y, jugador.get_invertido());
            jugador.disparar(bala3->disparar());
            balas.push_back(std::move(bala3));
            break;
        }
        default:
            return;
    }
}

bool hay_colision_bala(int32_t bala_x, int32_t bala_y, int32_t target_x, int32_t target_y,
                       int32_t ancho, int32_t alto) {
    return ((target_x < bala_x) && (bala_x < target_x + ancho) && (target_y < bala_y) &&
            (bala_y < target_y + alto));
}

void manejadorEscenario::generar_objeto_aleatorio(int32_t pos_x, int32_t pos_y) {
    const ConfigAdmin& configurador = ConfigAdmin::getInstance();
    int prob_com = configurador.get(PROBABILIDAD_COM);
    int prob_mun = configurador.get(PROBABILIDAD_MUN);
    srand(pos_x + pos_y);
    if (rand() % (prob_com + prob_mun) < prob_com) {  // si el objeto es una comida
        int prob_buena = configurador.get(PROB_COM_BUENA);
        int prob_mala = configurador.get(PROB_COM_MALA);
        if (rand() % (prob_buena + prob_mala) < prob_buena) {
            objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, FRUTA_BUENA);
        } else {
            objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, FRUTA_PODRIDA);
        }
    } else {  // si el objeto es municion
        int prob_1 = configurador.get(PROB_MUN_1);
        int prob_2 = configurador.get(PROB_MUN_2);
        int prob_3 = configurador.get(PROB_MUN_3);
        if (const int num = rand() % (prob_1 + prob_2 + prob_3) < prob_1) {
            objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, MUNICION_ARMA_1);
        } else if (num < prob_1 + prob_2) {
            objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, MUNICION_ARMA_2);
        } else {
            objetos.emplace_back(pos_x, pos_y, TAMANO_BLOQUE, TAMANO_BLOQUE, MUNICION_ARMA_3);
        }
    }
}

void manejadorEscenario::manejar_balas(std::map<int, personaje>& jugadores) {
    for (auto it = balas.begin(); it != balas.end();) {
        if ((*it)->mover()) {
            it = balas.erase(it);
            continue;
        }
        std::vector<int32_t> posicion_bala = (*it)->get_pos();
        int32_t bala_x = posicion_bala[0];
        int32_t bala_y = posicion_bala[1];
        for (auto& jugador: jugadores) {
            personaje& jug = jugador.second;
            const std::vector<int32_t> posicion = jug.get_pos_actual();
            const int32_t jug_x = posicion[0];
            const int32_t jug_y = posicion[1];
            if (((*it)->get_id() != jugador.first) &&
                hay_colision_bala(bala_x, bala_y, jug_x, jug_y, jug.get_ancho(), jug.get_alto())) {
                int32_t dano = (*it)->impactar();
                jug.efectuar_dano(dano);
            }
        }
        for (auto& en: enemigos) {
            if (en.get_estado() != MUERTO &&
                hay_colision_bala(bala_x, bala_y, en.get_pos_x(), en.get_pos_y(), en.get_ancho(),
                                  en.get_alto())) {
                int32_t dano = (*it)->impactar();
                if (en.hacer_dano(dano)) {
                    jugadores.at((*it)->get_id()).dar_puntos(en.get_puntos());
                }
            }
        }
        for (const auto& bloque: bloques_rectos) {
            if (hay_colision_bala(bala_x, bala_y, bloque.pos_x, bloque.pos_y, bloque.ancho,
                                  bloque.alto)) {
                (*it)->impactar();
            }
        }
        for (const auto& bloque: bloques_angulados) {
            if (hay_colision_bala(bala_x, bala_y, bloque.pos_x, bloque.pos_y, bloque.ancho,
                                  bloque.alto)) {
                (*it)->impactar();
            }
        }
    }
}
