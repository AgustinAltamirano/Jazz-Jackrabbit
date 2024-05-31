#include "manejadorEscenario.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

#include "../../common/constantes.h"

manejadorEscenario::manejadorEscenario(std::string path): path(std::move(path)) {
    cargar_escenario_basico(620, 480);
}

void manejadorEscenario::cargar_escenario_basico(uint32_t ancho, uint32_t alto) {
    // esto crea un generico de 620 x 480 para pruebas de colision
    bloques_rectos.emplace_back(0, alto, ancho, 10, 0, PISO);
    bloques_rectos.emplace_back(0, 0, ancho, 10, 0, TECHO);
    bloques_rectos.emplace_back(0, 0, 10, alto, 0, PARED);
    bloques_rectos.emplace_back(ancho - 10, 0, 10, alto, 0, PARED);
    spawnpoints.emplace_back(ANCHO_INICIAL + 10, alto - ALTO_INICIAL);
}

std::vector<spawnpoint>& manejadorEscenario::get_spawns() { return spawnpoints; }


bool hay_colision_recta(const int32_t jug_x, const int32_t jug_y, const uint32_t alto,
                        const uint32_t ancho, const bloqueEscenario& bloque) {
    return (jug_x < bloque.pos_x + bloque.ancho && jug_x + ancho > bloque.pos_x &&
            jug_y < bloque.pos_y + bloque.alto && jug_y + alto > bloque.pos_y);
}

std::vector<bloqueEscenario> chequeo_recto_individual(const personaje& jugador,
                                                      const std::vector<bloqueEscenario>& bloques) {
    std::vector<bloqueEscenario> colisiones;
    const std::vector<int> posicion_prox = jugador.get_pos_a_ir();
    int jug_x = posicion_prox[0];
    int jug_y = posicion_prox[1];
    colisiones.reserve(bloques.size());
    std::copy_if(bloques.begin(), bloques.end(), std::back_inserter(colisiones),
                 [&](const bloqueEscenario& bloque) {
                     return hay_colision_recta(jug_x, jug_y, jugador.get_alto(),
                                               jugador.get_ancho(), bloque);
                 });
    return colisiones;
}

uint32_t definir_punto_medio(const int32_t pos_org_jug, const uint32_t jug_largo,
                             const int32_t pos_bloque, const uint32_t bloque_largo) {
    if (pos_org_jug < pos_bloque) {  // si este es el caso ajusto por arriba o por izquierda
        return (pos_bloque - jug_largo);
    }
    return (pos_bloque + bloque_largo);
}

bool colision_horizontal(const int32_t jug_x, const uint32_t jug_ancho,
                         const bloqueEscenario& bloque) {
    return ((jug_x + jug_ancho > bloque.pos_x && jug_x < bloque.pos_x) ||
            (jug_x < bloque.pos_x + bloque.ancho &&
             jug_x + jug_ancho > bloque.pos_x + bloque.ancho));
}

bool colision_vertical(const int32_t jug_y, const uint32_t jug_alto,
                       const bloqueEscenario& bloque) {
    return ((jug_y + jug_alto > bloque.pos_y && jug_y < bloque.pos_y) ||
            (jug_y < bloque.pos_y + bloque.alto && jug_y + jug_alto > bloque.pos_y + bloque.alto));
}

void manejadorEscenario::colisiones_bloques_rectos(std::map<int, personaje>& jugadores) const {
    for (auto& entidad: jugadores) {
        personaje& jugador = entidad.second;
        std::vector<bloqueEscenario> colisiones = chequeo_recto_individual(jugador, bloques_rectos);

        std::vector<int> posicion_act = jugador.get_pos_actual();
        std::vector<int> posicion_prox = jugador.get_pos_a_ir();
        int32_t pos_x_jug_act = posicion_act[0], pos_y_jug_act = posicion_act[1];
        int32_t pos_x_jug_prox = posicion_prox[0], pos_y_jug_prox = posicion_prox[1];
        uint32_t nueva_pos_x = pos_x_jug_prox, nueva_pos_y = pos_y_jug_prox;
        for (const auto& bloque: colisiones) {
            bool col_vert = colision_vertical(pos_y_jug_prox, jugador.get_alto(), bloque);
            bool col_hor = colision_horizontal(pos_x_jug_prox, jugador.get_ancho(), bloque);
            if (!col_hor && col_vert) {  // si solo hay colision vertical
                nueva_pos_y = definir_punto_medio(pos_y_jug_act, jugador.get_alto(), bloque.pos_y,
                                                  bloque.alto);
            } else if (col_hor && !col_vert) {  // si solo hay colision horizontal
                nueva_pos_x = definir_punto_medio(pos_x_jug_act, jugador.get_ancho(), bloque.pos_x,
                                                  bloque.ancho);
            } else {  // si hay colision por ambos lados
                const int32_t inter_x = std::min(pos_x_jug_prox + jugador.get_ancho(),
                                                 bloque.pos_x + bloque.ancho) -
                                        std::max(pos_x_jug_prox, bloque.pos_x);
                const int32_t inter_y =
                        std::min(pos_y_jug_prox + jugador.get_alto(), bloque.pos_y + bloque.alto) -
                        std::max(pos_y_jug_prox, bloque.pos_y);
                if (inter_x > inter_y) {
                    nueva_pos_y = definir_punto_medio(pos_y_jug_act, jugador.get_alto(),
                                                      bloque.pos_y, bloque.alto);
                } else {
                    nueva_pos_x = definir_punto_medio(pos_x_jug_act, jugador.get_ancho(),
                                                      bloque.pos_x, bloque.ancho);
                }
            }
        }
        jugador.cambiar_posicion(nueva_pos_x, nueva_pos_y);
    }
}
