#include "partida.h"

#include <chrono>
#include <cmath>
#include <string>

#include <unistd.h>

#include "logica_juego/gameloop.h"

double frecuencia = 0.05;

Partida::Partida(Queue<SnapshotDTO>* cola_enviador, int32_t& codigo_partida,
                 std::string& nombre_escenario, const int32_t& id_cliente, TipoPersonaje& personaje,
                 int8_t& capacidad_partida):
        cola_comandos(10000),
        nombre_escenario(nombre_escenario),
        codigo_partida(capacidad_partida),
        sigo_jugando(true),
        admite_jugadores(true),
        capacidad_partida(capacidad_partida) {
    monitor_snapshots.agregar_cola(cola_enviador, id_cliente);
    mapa_clientes_juego[id_cliente] = personaje;
}

void Partida::run() {
    while (mapa_clientes_juego.size() < capacidad_partida && sigo_jugando) {
        try {
            std::this_thread::sleep_for(std::chrono::duration<double>(frecuencia));
        } catch (const ClosedQueue& e) {
            std::cout << "Partida finalizada" << std::endl;
            sigo_jugando = false;
            return;
        }
    }
    admite_jugadores = false;
    // Llamo al gameloop
    Gameloop gameloop(nombre_escenario, mapa_clientes_juego, cola_comandos, monitor_snapshots);
    gameloop.run();
    cola_comandos.close();
}

Queue<ComandoDTO*>* Partida::obtener_comandos() { return &cola_comandos; }

void Partida::agregar_cliente(Queue<SnapshotDTO>* cola_enviador, const int32_t& id_cliente,
                              const TipoPersonaje& personaje) {
    mapa_clientes_juego[id_cliente] = personaje;
    monitor_snapshots.agregar_cola(cola_enviador, id_cliente);
}

bool Partida::comparar_codigo_partida(const int32_t& codigo_a_comparar) {
    return (codigo_partida == codigo_a_comparar);
}

bool Partida::borrar_cliente(int32_t& id_cliente) {
    return monitor_snapshots.borrar_cliente(id_cliente);
}

bool Partida::esta_vacia() {
    if (monitor_snapshots.obtener_cantidad_clientes() == 0) {
        detener_partida();
        return true;
    }
    return false;
}

void Partida::detener_partida() { sigo_jugando = false; }

int32_t Partida::obtener_codigo_partida() { return codigo_partida; }

bool Partida::puedo_unir() {
    return (admite_jugadores && monitor_snapshots.obtener_cantidad_clientes() < capacidad_partida);
}

bool Partida::esta_jugando() { return sigo_jugando; }

void Partida::stop() { sigo_jugando = false; }
