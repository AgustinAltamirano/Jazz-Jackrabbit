#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "cliente.h"
#include "../common/snapshot_dto.h"

#include <map>
#include <memory>

class Gameloop {
    int id_cliente;
    Cliente cliente;
    double frecuencia;

public:
    Gameloop(int id_cliente, Socket &socket);

    ~Gameloop();

    void start();

private:
    void ejecutarCicloPrincipalJuego(SnapshotDTO &snapshot_dto);
};

#endif //GAMELOOP_H
