#include "gestor_partidas.h"

#include <iostream>
#include <numeric>

GestorPartidas::GestorPartidas() { contador_partidas = 1; }

Queue<ComandoDTO*>* GestorPartidas::crear_partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador,
                                                  std::string& nombre_escenario,
                                                  int32_t& id_cliente, int32_t& codigo_partida,
                                                  TipoPersonaje& personaje,
                                                  int8_t& capacidad_partidas) {
    std::lock_guard<std::mutex> lock(m);
    codigo_partida = contador_partidas;
    Partida* nueva_partida = new Partida(cola_enviador, codigo_partida, nombre_escenario,
                                         id_cliente, personaje, capacidad_partidas);
    partidas[codigo_partida] = nueva_partida;
    std::cout << codigo_partida << std::endl;
    contador_partidas++;
    Queue<ComandoDTO*>* aux = nueva_partida->obtener_comandos();
    nueva_partida->start();
    return (aux);
}

bool GestorPartidas::existe_partida_por_codigo(int codigo) {
    auto partida_encontrada = partidas.find(codigo);
    return partida_encontrada != partidas.end();
}

Partida* GestorPartidas::obtener_partida_por_codigo(int codigo) {
    auto partida_encontrada = partidas.find(codigo);
    return partida_encontrada->second;
}

Queue<ComandoDTO*>* GestorPartidas::unir_partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, int32_t& codigo,
                                                 const int32_t& id_cliente,
                                                 const TipoPersonaje& personaje) {
    std::lock_guard<std::mutex> lock(m);

    if (not existe_partida_por_codigo(codigo)) {
        std::cout << "No existe la partida" << std::endl;
        return nullptr;
    }

    Partida* partida = obtener_partida_por_codigo(codigo);

    std::cout << "pedido para agregar" << std::endl;
    if (partida && partida->puedo_unir()) {
        std::cout << "agregue cliente a la partida" << std::endl;
        partida->agregar_cliente(cola_enviador, id_cliente, personaje);
        return partida->obtener_comandos();
    }
    return nullptr;
}

void GestorPartidas::join_partidas() {
    std::lock_guard<std::mutex> lock(m);
    for (const auto& par : partidas) {
        auto partida = par.second;
        partida->detener_partida();
        partida->join();
        delete partida;
    }
    partidas.clear();
}

void GestorPartidas::borrar_cliente(int32_t& id_cliente) {
    // Si al elimintar me quede sin clientes elimino la partida
    std::lock_guard<std::mutex> lock(m);
    for (const auto& par : partidas) {
        auto codigo_partida = par.first;
        auto partida = par.second;
        if (partida->borrar_cliente(id_cliente)) {
            partida->detener_partida();
            break;
        }
    }
}

void GestorPartidas::borrar_partidas_finalizadas() {
    std::lock_guard<std::mutex> lock(m);
    std::vector<int> codigos_a_eliminar;

    for (const auto& par : partidas) {
        auto codigo_partida = par.first;
        auto partida = par.second;
        if (!partida->esta_jugando()) {
            partida->join();
            delete partida;
            codigos_a_eliminar.push_back(codigo_partida);
        }
    }

    for (const auto& codigo : codigos_a_eliminar) {
        partidas.erase(codigo);
    }
}
