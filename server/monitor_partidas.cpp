#include "./monitor_partidas.h"

void MonitorPartidas::agregar_nueva_partida(Partida *partida) {
    std::lock_guard<std::mutex> lock(m);
    lista_partidas.push_back(partida);
}

int MonitorPartidas::obtener_cantidad_partidas() {
    std::lock_guard<std::mutex> lock(m);
    return lista_partidas.size();
}

Partida *MonitorPartidas::obtener_partidas_por_codigo(const int32_t &codigo_partida) {
    Partida *partida_encontrada = nullptr;
    std::lock_guard<std::mutex> lock(m);
    for (Partida *partida: lista_partidas) {
        if (partida->comparar_partida(codigo_partida))
            partida_encontrada = partida;
    }
    return partida_encontrada;
}

void MonitorPartidas::join_partidas() {
    std::lock_guard<std::mutex> lock(m);
    for (Partida *partida: lista_partidas) {
        partida->detener_partida();
        partida->join();
        delete partida;
    }
    lista_partidas.clear();
}

bool MonitorPartidas::borrar_cliente(int32_t &id_cliente) {
    std::lock_guard<std::mutex> lock(m);
    for (Partida *partida: lista_partidas) {
        if (partida->borrar_cliente(id_cliente)) {
            if (partida->esta_vacia()) {
                partida->join();
                delete partida;
                lista_partidas.remove(partida);
                return true;
            }
            break;
        }
    }
    return false;
}

void MonitorPartidas::eliminar_partidas_finalizadas() {
    std::lock_guard<std::mutex> lock(m);
    lista_partidas.remove_if([](Partida *p) {
        if (!p->esta_jugando()) {
            p->join();
            delete p;
            return true;
        }
        return false;
    });
}