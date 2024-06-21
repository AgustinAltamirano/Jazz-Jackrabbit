#include "partida.h"

#include <chrono>
#include <cmath>
#include <memory>
#include <string>

#include <unistd.h>

#include "logica_juego/gameloop.h"

double frecuencia = 0.05;

Partida::Partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, int32_t codigo_partida,
                 std::string& nombre_escenario, const int32_t& id_cliente, TipoPersonaje& personaje,
                 const int8_t& capacidad_partida):
        mapa_clientes_juego(),
        cola_snapshots(),
        codigo_partida(codigo_partida),
        nombre_escenario(nombre_escenario),
        cola_comandos(10000),
        sigo_jugando(true),
        cantidad_jugadores(1),
        comenzada(false),
        capacidad_partida(capacidad_partida) {
    mapa_clientes_juego[id_cliente] = personaje;
    cola_snapshots[id_cliente] = cola_enviador;
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

void Partida::detener_partida() {
    if (!sigo_jugando) {
        return;
    }
    sigo_jugando = false;
    cola_comandos.close();
    // Si el cliente se desconecta o se desea cerrar el server, se envía un snapshot de fin de juego
    const auto snapshot_fin_juego = std::make_shared<SnapshotDTO>();
    snapshot_fin_juego->establecer_fin_juego(true);
    for (auto& [codigo, cola_salida]: cola_snapshots) {
        cola_salida->push(snapshot_fin_juego);
    }
}

int32_t Partida::obtener_codigo_partida() { return codigo_partida; }

bool Partida::no_esta_comenzada() { return !comenzada; }

bool Partida::esta_jugando() { return sigo_jugando; }

Partida::~Partida() = default;

void Partida::stop() { sigo_jugando = false; }
