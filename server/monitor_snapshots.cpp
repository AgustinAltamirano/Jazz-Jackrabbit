#include "./monitor_snapshots.h"
#include <iostream>

void MonitorSnapshots::agregar_snapshot(SnapshotDTO &snapshot_dto) {
    std::lock_guard<std::mutex> lock(m);
    for (const auto &cola: cola_snapshots) {
        cola.second->try_push(snapshot_dto);
    }
}

void MonitorSnapshots::agregar_cola(Queue<SnapshotDTO> *cola_snapshot, int32_t &id_jugador) {
    std::lock_guard<std::mutex> lock(m);
    cola_snapshots[id_jugador] = cola_snapshot;
}

int MonitorSnapshots::obtener_cantidad_clientes() {
    std::lock_guard<std::mutex> lock(m);
    return cola_snapshots.size();
}

bool MonitorSnapshots::borrar_cliente(int32_t &id_cliente) {
    std::lock_guard<std::mutex> lock(m);
    auto it = cola_snapshots.find(id_cliente);
    if (it != cola_snapshots.end()) {
        cola_snapshots.erase(it);
        return true;
    }
    return false;
}