#ifndef MANEJADORESCENARIO_H
#define MANEJADORESCENARIO_H

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../client/vista_juego/snapshot_dto.h"
#include "assets/bloqueEscenario.h"
#include "assets/recogible.h"
#include "assets/spawnpoint.h"

#include "personaje.h"

class manejadorEscenario {
private:
    std::string path;
    uint32_t ancho;
    uint32_t alto;
    TipoEscenario clase_escenario;
    std::vector<bloqueEscenario> bloques_rectos;
    std::vector<bloqueEscenario> bloques_angulados;
    std::vector<spawnpoint> spawnpoints;
    std::list<recogible> objetos;

public:
    // creacion, cargar escenario y ayudar a gameloop
    explicit manejadorEscenario(std::string path);
    void cargar_escenario_basico(uint32_t ancho, uint32_t alto);
    std::vector<spawnpoint>& get_spawns();
    TipoEscenario get_escenario();

    // chequeo colision con bloques
    void colisiones_bloques_rectos(std::map<int, personaje>& jugadores) const;
    void colisiones_bloques_angulo(const std::map<int, personaje>& jugadores) const;
    void chequear_caida_y_objetos(std::map<int, personaje>& jugadores);

    // crear snapshots
    auto crear_snapshot();
};


#endif  // MANEJADORESCENARIO_H
