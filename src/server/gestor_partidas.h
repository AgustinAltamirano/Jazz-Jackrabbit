#ifndef GESTOR_PARTIDAS_H
#define GESTOR_PARTIDAS_H

#include <atomic>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "../common/queue.h"

#include "partida.h"

class GestorPartidas {
private:
    std::mutex m;

    std::map<int32_t, Partida*> partidas;

    int32_t contador_partidas;  // Corresponde con el codigo de partida.

    Partida* obtener_partida_por_codigo(int codigo);

    bool existe_partida_por_codigo(int codigo);

public:
    GestorPartidas();

    Queue<ComandoDTO*>* crear_partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador,
                                      std::string& nombre_escenario, int32_t& id_cliente,
                                      int32_t& codigo_partida, TipoPersonaje& personaje,
                                      int8_t& capacidad_partidas);

    Queue<ComandoDTO*>* unir_partida(Queue<std::shared_ptr<SnapshotDTO>>* queue_sender, int32_t& codigo_partida,
                                     const int32_t& id_cliente, const TipoPersonaje& personaje);

    void join_partidas();

    void borrar_cliente(int32_t& id_cliente);

    void borrar_partidas_finalizadas();
};

#endif
