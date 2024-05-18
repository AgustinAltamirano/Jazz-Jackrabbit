#include <iostream>
#include "juego.h"

#define EXITO 0
#define FRACASO 1


Juego::Juego(MonitorPartidas &monitor_partidas) :
        monitor_partidas(monitor_partidas) {}


std::uint32_t
Juego::iniciar_partida(Queue<std::string> &cola_jugador) {
    monitor_partida =
            monitor_partidas.iniciar_partida(cola_jugador,
                                             codigo_partida);
    std::string mensaje = "Partida creada: ";
    imprimir(mensaje, codigo_partida);
    return codigo_partida;
}

bool Juego::unir_a_partida(Queue<std::string> &cola_jugador,
                           std::uint32_t codigo_partida_join) {
    monitor_partida = monitor_partidas.unirse_a_partida(cola_jugador,
                                                        codigo_partida_join);
    if (!monitor_partida) {
        std::string mensaje = "Partida inexistente: ";
        imprimir(mensaje, codigo_partida_join);
        return false;
    } else {
        codigo_partida = codigo_partida_join;
        std::string mensaje = "Unido a partida: ";
        imprimir(mensaje, codigo_partida);
        return true;
    }
}

void Juego::enviar_mensaje(const std::string &mensaje) {
    monitor_partida->enviar_mensaje(mensaje);
}

void Juego::imprimir(const std::string &mensaje,
                     const std::uint32_t &codigo) {
    std::string mensaje_completo =
            mensaje + std::to_string(codigo) + "\n";
    std::cout << mensaje_completo;
}
