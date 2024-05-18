#include "monitor_partidas.h"
#include "../common/constantes.h"


MonitorPartidas::MonitorPartidas() {}

MonitorPartida *
MonitorPartidas::iniciar_partida(Queue<std::string> &cola_jugador,
                                 std::uint32_t &codigo_partida) {
    int cant_max_partidas = config.get(MAX_PARTIDAS);
    if (codigo_unico >= cant_max_partidas) return NULL;
    MonitorPartida *sala = new MonitorPartida(cola_jugador);
    std::lock_guard<std::mutex> lck(mutex_map);
    codigo_partida = codigo_unico++;
    partidas[codigo_partida] = sala;
    return sala;
}

MonitorPartida *
MonitorPartidas::unirse_a_partida(Queue<std::string> &cola_jugador,
                                  std::uint32_t codigo_partida) {
    std::lock_guard<std::mutex> lck(mutex_map);
    int existe = partidas.count(codigo_partida);
    if (existe == 0) return NULL;
    int cant_max_jugadores_pp = config.get(MAX_JUG_POR_PARTIDA);
    if (partidas[codigo_partida]->obtener_cantidad_jugadores() >= cant_max_jugadores_pp) return NULL;
    partidas[codigo_partida]->unir_jugador(cola_jugador);
    return partidas[codigo_partida];
}

MonitorPartidas::~MonitorPartidas() {
    std::lock_guard<std::mutex> lck(mutex_map);
    for (auto it = partidas.begin(); it != partidas.end(); ++it) {
        delete it->second;
    }
    partidas.clear();
}
