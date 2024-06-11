#include "./monitor_mapa_clientes.h"

#include <iostream>

void MonitorMapaClientes::agregar_cliente(int id_cliente, TipoPersonaje personaje) {
    std::lock_guard<std::mutex> lock(m);
    mapa_clientes_juego[id_cliente] = personaje;
}

int MonitorMapaClientes::obtener_cantidad_clientes() {
    std::lock_guard<std::mutex> lock(m);
    return mapa_clientes_juego.size();
}

std::map<int, TipoPersonaje> MonitorMapaClientes::obtener_clientes() {
    std::lock_guard<std::mutex> lock(m);
    return mapa_clientes_juego;
}