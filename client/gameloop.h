#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "cliente.h"
#include "../common/snapshot_dto.h"

#include <map>
#include <memory>

class Gameloop {
    Cliente cliente;
    double frecuencia;

public:
    Gameloop(const std::string &hostname, const std::string &servname);

    ~Gameloop();

    void start();

private:
    void ejecutarCicloPrincipalJuego(SnapshotDTO &snapshot_dto);
};

#endif //GAMELOOP_H
