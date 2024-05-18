#ifndef MONITOR_PARTIDAS_H_
#define MONITOR_PARTIDAS_H_


#include <map>
#include <vector>
#include <atomic>
#include <string>
#include "../common/queue.h"
#include "monitor_partida.h"
#include "../common/config.h"

class MonitorPartidas {
private:
    std::map<std::uint32_t, MonitorPartida *> partidas;
    std::mutex mutex_map;
    std::atomic<std::uint32_t> codigo_unico{0};
    ConfigAdmin config;

public:
    MonitorPartidas();

    MonitorPartida *iniciar_partida(Queue<std::string> &cola_jugador,
                                    std::uint32_t &codigo_partida);

    MonitorPartida *unirse_a_partida(Queue<std::string> &cola_jugador,
                                     std::uint32_t codigo_partida);

    ~MonitorPartidas();

    MonitorPartidas(const MonitorPartidas &) = delete;

    MonitorPartidas &operator=(const MonitorPartidas &) = delete;
};

#endif  //  MONITOR_PARTIDAS_H_
