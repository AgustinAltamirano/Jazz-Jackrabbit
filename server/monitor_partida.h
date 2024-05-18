#ifndef MONITOR_PARTIDA_H_
#define MONITOR_PARTIDA_H_

#include <vector>
#include <string>
#include "../common/queue.h"

class MonitorPartida {
private:
    std::vector<std::reference_wrapper<Queue<std::string>>>
            jugadores_partida;
    std::mutex mutex_partida;

public:
    explicit MonitorPartida(Queue<std::string> &queue);

    void unir_jugador(Queue<std::string> &queue);

    void enviar_mensaje(const std::string &mensaje);

    int obtener_cantidad_jugadores();

    MonitorPartida(const MonitorPartida &) = delete;

    MonitorPartida &operator=(const MonitorPartida &) = delete;
};

#endif  // MONITOR_PARTIDA_H_
