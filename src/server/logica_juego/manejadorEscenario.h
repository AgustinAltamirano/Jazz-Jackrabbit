#ifndef MANEJADORESCENARIO_H
#define MANEJADORESCENARIO_H

#include <map>
#include <string>
#include <vector>

#include "assets/bloqueEscenario.h"
#include "assets/spawnpoint.h"

#include "personaje.h"

class manejadorEscenario {
private:
    std::string path;
    std::vector<bloqueEscenario> bloques_rectos;
    std::vector<bloqueEscenario> bloques_angulados;
    std::vector<spawnpoint> spawnpoints;

public:
    explicit manejadorEscenario(std::string path);
    void cargar_escenario_basico(uint32_t ancho, uint32_t alto);
    void colisiones_bloques_rectos(std::map<int, personaje>& jugadores) const;
    std::vector<spawnpoint>& get_spawns();
};


#endif  // MANEJADORESCENARIO_H
