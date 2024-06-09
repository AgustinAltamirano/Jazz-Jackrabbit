#ifndef MATCHMANANGER_H
#define MATCHMANANGER_H

#include <atomic>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "../common/queue.h"
#include "./monitor_partidas.h"

#include "partida.h"

class GestorPartidas {
private:
    int32_t contador_partidas;  // Corresponde con el codigo de partida.

    MonitorPartidas monitor_partidas;

    Partida* existe_partida_por_codigo(const int& codigo);

public:
    GestorPartidas();

    Queue<ComandoDTO*>* crear_partida(Queue<SnapshotDTO>* cola_enviador,
                                      std::string& nombre_escenario, int32_t& id_cliente,
                                      int32_t& codigo_partida, TipoPersonaje& personaje,
                                      int8_t& capacidad_partidas);

    Queue<ComandoDTO*>* unir_partida(Queue<SnapshotDTO>* queue_sender, int32_t& codigo_partida,
                                     const int32_t& id_cliente, const TipoPersonaje& personaje);

    void join_partidas();

    void borrar_cliente(int32_t& id_cliente);

    void borrar_partidas_finalizadas();
};

#endif
