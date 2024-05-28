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
    void cargar_escenario_basico(int ancho, int alto);
    void colisiones_bloques_rectos(std::map<int, personaje>& jugadores) const;
};


#endif  // MANEJADORESCENARIO_H
