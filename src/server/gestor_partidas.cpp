#include "gestor_partidas.h"

#include <iostream>
#include <memory>
#include <numeric>

GestorPartidas::GestorPartidas() { contador_partidas = 1; }

Queue<std::shared_ptr<ComandoServer>>* GestorPartidas::crear_partida(
        Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, std::string& nombre_escenario,
        const int32_t& id_cliente, int32_t& codigo_partida, TipoPersonaje& personaje,
        const int8_t& capacidad_partidas) {
    std::lock_guard<std::mutex> lock(m);
    codigo_partida = contador_partidas;

    partidas.emplace(std::piecewise_construct, std::forward_as_tuple(codigo_partida),
                     std::forward_as_tuple(cola_enviador, codigo_partida, nombre_escenario,
                                           id_cliente, personaje, capacidad_partidas));

    contador_partidas++;
    return partidas.at(codigo_partida).obtener_comandos();
}

bool GestorPartidas::existe_partida_por_codigo(int codigo) {
    auto partida_encontrada = partidas.find(codigo);
    return partida_encontrada != partidas.end();
}

Partida& GestorPartidas::obtener_partida_por_codigo(const int codigo) {
    const auto partida_encontrada = partidas.find(codigo);
    return partida_encontrada->second;
}

Queue<std::shared_ptr<ComandoServer>>* GestorPartidas::unir_partida(
        Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, const int32_t& codigo,
        const int32_t& id_cliente, const TipoPersonaje& personaje) {
    std::lock_guard<std::mutex> lock(m);

    if (not existe_partida_por_codigo(codigo)) {
        std::cout << "No existe la partida" << std::endl;
        return nullptr;
    }

    Partida& partida = obtener_partida_por_codigo(codigo);

    if (partida.no_esta_comenzada()) {
        partida.agregar_cliente(cola_enviador, id_cliente, personaje);
        if (!partida.no_esta_comenzada()) {
            partida.start();
        }
        return partida.obtener_comandos();
    }
    return nullptr;
}

void GestorPartidas::join_partidas() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& par: partidas) {
        auto& partida = par.second;
        partida.detener_partida();
        if (!partida.no_esta_comenzada()) {
            partida.join();
        }
    }
}

void GestorPartidas::borrar_cliente(int32_t& id_cliente) {
    // Si al elimintar me quede sin clientes elimino la partida
    std::lock_guard<std::mutex> lock(m);
    for (auto& par: partidas) {
        auto& partida = par.second;
        if (partida.borrar_cliente(id_cliente)) {
            partida.detener_partida();
            break;
        }
    }
}

void GestorPartidas::borrar_partidas_finalizadas() {
    std::lock_guard<std::mutex> lock(m);
    std::vector<int> codigos_a_eliminar;

    for (auto& par: partidas) {
        auto codigo_partida = par.first;
        auto& partida = par.second;
        if (!partida.esta_jugando()) {
            partida.join();
            codigos_a_eliminar.push_back(codigo_partida);
        }
    }

    for (const auto& codigo: codigos_a_eliminar) {
        partidas.erase(codigo);
    }
}
