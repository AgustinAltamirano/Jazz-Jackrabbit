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
    lista_partidas.push_back(nueva_partida);
    std::cout << codigo_partida << std::endl;
    contador_partidas++;
    Queue<ComandoDTO*>* aux = nueva_partida->obtener_comandos();
    nueva_partida->start();
    return (aux);
}

Partida* GestorPartidas::existe_partida_por_codigo(int codigo) {
    Partida* partida_encontrada = std::accumulate(
            lista_partidas.begin(), lista_partidas.end(), static_cast<Partida*>(nullptr),
            [codigo](Partida* encontrado, Partida* partida) {
                if (encontrado)
                    return encontrado;
                if (partida->comparar_codigo_partida(codigo))
                    return partida;
                return static_cast<Partida*>(nullptr);
            });
    return partida_encontrada;
}

Queue<ComandoDTO*>* GestorPartidas::unir_partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, int32_t& codigo,
                                                 const int32_t& id_cliente,
                                                 const TipoPersonaje& personaje) {
    std::lock_guard<std::mutex> lock(m);
    Partida* partida = existe_partida_por_codigo(codigo);
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
    for (Partida* partida: lista_partidas) {
        partida->detener_partida();
        partida->join();
        delete partida;
    }
    lista_partidas.clear();
}

void GestorPartidas::borrar_cliente(int32_t& id_cliente) {
    // Si al elimintar me quede sin clientes elimino la partida
    std::lock_guard<std::mutex> lock(m);
    for (Partida* partida: lista_partidas) {
        if (partida->borrar_cliente(id_cliente)) {
            if (partida->esta_vacia()) {
                partida->join();
                delete partida;
                lista_partidas.remove(partida);
                contador_partidas--;
                return;
            }
            break;
        }
    }
}

void GestorPartidas::borrar_partidas_finalizadas() {
    std::lock_guard<std::mutex> lock(m);
    lista_partidas.remove_if([](Partida* p) {
        if (!p->esta_jugando()) {
            p->join();
            delete p;
            return true;
        }
        return false;
    });
}
