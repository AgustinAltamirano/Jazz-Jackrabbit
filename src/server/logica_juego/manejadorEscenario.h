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
    // creacion, cargar escenario y ayudar a gameloop
    explicit manejadorEscenario(std::string path);
    void cargar_escenario_basico(uint32_t ancho, uint32_t alto);
    std::vector<spawnpoint>& get_spawns();

    // chequeo colision con bloques
    void colisiones_bloques_rectos(std::map<int, personaje>& jugadores) const;
    void colisiones_bloques_angulo(const std::map<int, personaje>& jugadores) const;
    void chequear_caida(const std::map<int, personaje>& jugadores) const;
};


#endif  // MANEJADORESCENARIO_H
