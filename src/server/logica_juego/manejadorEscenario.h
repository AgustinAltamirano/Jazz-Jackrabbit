#ifndef MANEJADORESCENARIO_H
#define MANEJADORESCENARIO_H

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../common/snapshot_dto.h"
#include "../../common/tipo_escenario.h"
#include "assets/bala.h"
#include "assets/balaInfinita.h"
#include "assets/bala_arma_1.h"
#include "assets/bala_arma_2.h"
#include "assets/bala_arma_3.h"
#include "assets/bloqueEscenario.h"
#include "assets/recogible.h"
#include "assets/spawnpoint.h"

#include "enemigo.h"
#include "esqueleto.h"
#include "lagarto.h"
#include "murcielago.h"
#include "personaje.h"

class manejadorEscenario {
private:
    std::string path;
    TipoEscenario clase_escenario;
    std::vector<bloqueEscenario> bloques_rectos;
    std::vector<bloqueEscenario> bloques_angulados;
    std::vector<spawnpoint> spawnpoints;
    std::vector<spawnpoint> spawnpoints_enemigos;
    std::list<std::unique_ptr<enemigo>> enemigos;
    std::list<std::unique_ptr<recogible>> objetos;
    std::list<std::unique_ptr<bala>> balas;
    int32_t limite_mapa_x;
    int32_t limite_mapa_y;

public:
    // creacion, cargar escenario y ayudar a gameloop
    explicit manejadorEscenario(std::string path);
    void cargar_escenario();
    void cargar_enemigos();
    std::vector<spawnpoint>& get_spawns();
    TipoEscenario get_escenario();

    // chequeo colision con bloques
    std::vector<bool> colisiones_bloques_y_enemigos(std::map<int, personaje>& jugadores);
    void chequear_caida_y_objetos(std::map<int, personaje>& jugadores);

    // personaje disparo bala
    void jugador_dispara(int32_t id, personaje& jugador);
    std::vector<bool> manejar_balas(std::map<int, personaje>& jugadores, std::vector<bool> cambios);

    // manejo enemigos
    void hacer_tick_enemigos();
    void generar_objeto_aleatorio(int32_t pos_x, int32_t pos_y);
    void matar_enemigos() const;

    // crear snapshots
    std::shared_ptr<SnapshotDTO> crear_snapshot();
    std::shared_ptr<SnapshotDTO> crear_snapshot_partida();
};

#endif  // MANEJADORESCENARIO_H
