#include "partida.h"

#include <chrono>
#include <cmath>
#include <string>

#include <unistd.h>

double frecuencia = 0.05;

Partida::Partida(Queue<SnapshotDTO>* cola_enviador, int32_t& codigo_partida,
                 const int32_t& id_cliente, int8_t& capacidad_partida):
        cola_comandos(10000),
        codigo_partida(capacidad_partida),
        logica_juego(),
        sigo_jugando(true),
        admite_jugadores(true),
        capacidad_partida(capacidad_partida) {
    monitor_snapshots.agregar_cola(cola_enviador, id_cliente);
}

void Partida::run() {
    ComandoDTO* comando_dto;
    bool pop_comando;
    int capacidad_inicial = 0;
    while (capacidad_inicial < monitor_snapshots.obtener_cantidad_clientes() && sigo_jugando) {
        try {
            pop_comando = cola_comandos.try_pop(comando_dto);
            if (pop_comando) {
                if (comando_dto->obtener_comando() == COMENZAR) {
                    capacidad_inicial++;
                    delete comando_dto;
                }
            }
            std::this_thread::sleep_for(std::chrono::duration<double>(frecuencia));
        } catch (const ClosedQueue& e) {
            std::cout << "Partida finalizado" << std::endl;
            sigo_jugando = false;
            return;
        }
    }
    admite_jugadores = false;
    while (sigo_jugando) {
        auto t_inicio = std::chrono::high_resolution_clock::now();  // Comienzo el timer
        SnapshotDTO snapshot_dto = logica_juego.obtener_snapshot();
        monitor_snapshots.agregar_snapshot(snapshot_dto);
        auto t_fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracion = t_fin - t_inicio;
        double descanso = frecuencia - duracion.count();
        if (descanso < 0) {
            double adelanto = -descanso;
            double perdida = adelanto - std::fmod(adelanto, frecuencia);
            t_inicio += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
                    std::chrono::duration<double>(perdida));
        } else {
            std::this_thread::sleep_for(std::chrono::duration<double>(descanso));
        }
    }
    SnapshotDTO snapshot_dto = logica_juego.obtener_snapshot();
    snapshot_dto.establecer_fin_juego(true);
    monitor_snapshots.agregar_snapshot(snapshot_dto);
    cola_comandos.close();
}

Queue<ComandoDTO*>* Partida::obtener_comandos() { return &cola_comandos; }

void Partida::agregar_cliente(Queue<SnapshotDTO>* cola_enviador, const int32_t& id_cliente) {
    logica_juego.agregar_cliente(id_cliente);
    monitor_snapshots.agregar_cola(cola_enviador, id_cliente);
}

bool Partida::comparar_partida(const int32_t& codigo_a_comparar) {
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

bool Partida::still_alive() { return sigo_jugando; }

void Partida::kill() { sigo_jugando = false; }
