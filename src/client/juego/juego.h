#ifndef JUEGO_H
#define JUEGO_H

#include <map>
#include <memory>

#include "../../common/snapshot_dto.h"

#include "cliente.h"

class Juego {
    int id_cliente;
    Cliente cliente;
    double frecuencia;

public:
    Juego(int id_cliente, Socket& socket);

    ~Juego();

    void start();

private:
    void ejecutar_ciclo_principal_juego(SnapshotDTO& snapshot_dto);
};

#endif  // JUEGO_H
