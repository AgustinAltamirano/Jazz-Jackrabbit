#ifndef MATCHMANANGER_H
#define MATCHMANANGER_H

#include "../common/queue.h"
#include "./monitor_partidas.h"
#include "partida.h"

#include <map>
#include <list>
#include <vector>
#include <string>
#include <atomic>

class GestorPartidas {
private:
    int32_t contador_partidas;   //Corresponde con el codigo de partida.

    MonitorPartidas monitor_partidas;

    Partida *existe_partida_por_codigo(const int &codigo);

    void borrar_partidas_finalizadas();

public:
    GestorPartidas();

    Queue<ComandoDTO *> *crear_partida(Queue<SnapshotDTO> *cola_enviador,
                                       int32_t &id_cliente, int32_t &codigo_partida,
                                       int8_t &capacidad_partidas);

    Queue<ComandoDTO *> *unir_partida(Queue<SnapshotDTO> *queue_sender, int32_t &codigo_partida, int32_t &id_cliente);

    void join_partidas();

    void borrar_cliente(int32_t &id_cliente);
};

#endif

    
