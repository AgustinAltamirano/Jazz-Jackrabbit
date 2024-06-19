#include "partida.h"

#include <chrono>
#include <cmath>
#include <string>

#include <unistd.h>

#include "logica_juego/gameloop.h"

double frecuencia = 0.05;

Partida::Partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, int32_t codigo_partida,
                 std::string& nombre_escenario, const int32_t& id_cliente, TipoPersonaje& personaje,
                 int8_t& capacidad_partida):
        cola_comandos(10000),
        nombre_escenario(nombre_escenario),
        codigo_partida(codigo_partida),
        sigo_jugando(true),
        capacidad_partida(capacidad_partida),
        mapa_clientes_juego(),
        cola_snapshots() {
    mapa_clientes_juego[id_cliente] = personaje;
    cola_snapshots[id_cliente] = cola_enviador;
    cantidad_jugadores = 1;
    comenzada = false;
}

void Partida::run() {
    Gameloop gameloop(nombre_escenario, mapa_clientes_juego, cola_comandos, cola_snapshots,
                      sigo_jugando);
    gameloop.run();
}

Queue<ComandoServer*>* Partida::obtener_comandos() { return &cola_comandos; }

void Partida::agregar_cliente(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador,
                              const int32_t& id_cliente, const TipoPersonaje& personaje) {
    mapa_clientes_juego[id_cliente] = personaje;
    cola_snapshots[id_cliente] = cola_enviador;
    cantidad_jugadores++;
    if (cantidad_jugadores == capacidad_partida) {
        comenzada = true;
    }
}

bool Partida::comparar_codigo_partida(const int32_t& codigo_a_comparar) {
    return (codigo_partida == codigo_a_comparar);
}

bool Partida::borrar_cliente_mapa(int32_t& id_cliente) {
    auto it = mapa_clientes_juego.find(id_cliente);
    if (it != mapa_clientes_juego.end()) {
        mapa_clientes_juego.erase(it);
        return true;
    }
    return false;
}

bool Partida::borrar_cliente_snapshots(int32_t& id_cliente) {
    auto it = cola_snapshots.find(id_cliente);
    if (it != cola_snapshots.end()) {
        cola_snapshots.erase(it);
        return true;
    }
    return false;
}

bool Partida::borrar_cliente(int32_t& id_cliente) {
    return borrar_cliente_mapa(id_cliente) && borrar_cliente_snapshots(id_cliente);
}

bool Partida::esta_vacia() {
    if (cola_snapshots.size() == 0) {
        detener_partida();
        return true;
    }
    return false;
}

void Partida::detener_partida() { sigo_jugando = false; }

int32_t Partida::obtener_codigo_partida() { return codigo_partida; }

bool Partida::puedo_unir() { return !comenzada; }

bool Partida::esta_jugando() { return sigo_jugando; }

void Partida::stop() { sigo_jugando = false; }