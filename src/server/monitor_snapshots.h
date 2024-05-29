#ifndef MONITOR_SNAPSHOTS_H
#define MONITOR_SNAPSHOTS_H

#include "../common/queue.h"
#include "../common/snapshot_dto.h"

#include <map>

class MonitorSnapshots {
private:
    std::mutex m;

    std::map<int, Queue<SnapshotDTO> *> cola_snapshots;
public:
    void agregar_snapshot(SnapshotDTO &snapshot_dto);

    void agregar_cola(Queue<SnapshotDTO> *cola_snapshot, int32_t &id_jugador);

    int obtener_cantidad_clientes();

    bool borrar_cliente(int32_t &id_cliente);
};

#endif
