#ifndef JUEGO_H_
#define JUEGO_H_

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include "../common/queue.h"
#include "monitor_partidas.h"
#include "monitor_partida.h"

class Juego {
private:
    std::uint32_t codigo_partida = -1;
    MonitorPartidas &monitor_partidas;
    MonitorPartida *monitor_partida = NULL;

    void imprimir(const std::string &mensaje, const std::uint32_t &codigo);

public:
    explicit Juego(MonitorPartidas &monitor_partidas);

    std::uint32_t iniciar_partida(Queue<std::string> &cola_jugador);

    bool unir_a_partida(Queue<std::string> &cola_jugador,
                        std::uint32_t codigo_partida);

    void enviar_mensaje(const std::string &mensaje);

    Juego(const Juego &) = delete;

    Juego &operator=(const Juego &) = delete;
};

#endif  // JUEGO_H_
