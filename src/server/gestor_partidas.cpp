#include "gestor_partidas.h"

#include <iostream>

GestorPartidas::GestorPartidas() { contador_partidas = 0; }

Queue<ComandoDTO*>* GestorPartidas::crear_partida(Queue<SnapshotDTO>* cola_enviador,
                                                  const int32_t& id_cliente,
                                                  int32_t& codigo_partida,
                                                  int8_t& capacidad_partidas) {
    Partida* nueva_partida =
            new Partida(cola_enviador, codigo_partida, id_cliente, capacidad_partidas);
    monitor_partidas.agregar_nueva_partida(nueva_partida);
    codigo_partida = contador_partidas;
    contador_partidas++;
    Queue<ComandoDTO*>* aux = nueva_partida->obtener_comandos();
    nueva_partida->start();
    return (aux);
}

Partida* GestorPartidas::existe_partida_por_codigo(const int& codigo) {
    return monitor_partidas.obtener_partidas_por_codigo(codigo);
}

Queue<ComandoDTO*>* GestorPartidas::unir_partida(Queue<SnapshotDTO>* cola_enviador, int32_t& codigo,
                                                 const int32_t& id_cliente) {
    Partida* partida = existe_partida_por_codigo(codigo);
    if (partida && partida->puedo_unir()) {
        partida->agregar_cliente(cola_enviador, id_cliente);
        return partida->obtener_comandos();
    }
    return nullptr;
}

void GestorPartidas::join_partidas() { monitor_partidas.join_partidas(); }

void GestorPartidas::borrar_cliente(int32_t& id_cliente) {
    // Si al elimintar me quede sin clientes elimino la partida
    if (monitor_partidas.borrar_cliente(id_cliente))
        contador_partidas--;
}

void GestorPartidas::borrar_partidas_finalizadas() {
    monitor_partidas.eliminar_partidas_finalizadas();
}
