#ifndef PARTIDA_H
#define PARTIDA_H

#include <atomic>
#include <map>
#include <string>

#include "../common/comando_dto.h"
#include "../common/queue.h"
#include "../common/snapshot_dto.h"
#include "../common/thread.h"
#include "./monitor_snapshots.h"

#include "logica_juego.h"

class Partida: public Thread {
private:
    LogicaJuego logica_juego;

    MonitorSnapshots monitor_snapshots;

    int32_t codigo_partida;

    Queue<ComandoDTO*> cola_comandos;

    bool sigo_jugando;

    bool admite_jugadores;

    int8_t capacidad_partida;

public:
    Partida(Queue<SnapshotDTO>* cola_enviador, int32_t& codigo_partida, const int32_t& id_cliente,
            int8_t& capacidad_partida);

    void run() override;

    bool still_alive() override;

    void kill() override;

    Queue<ComandoDTO*>* obtener_comandos();

    void agregar_cliente(Queue<SnapshotDTO>* cola_enviador, const int32_t& id_cliente);

    bool comparar_partida(const int32_t& codigo_a_comparar);

    int32_t obtener_codigo_partida();

    bool borrar_cliente(int32_t& id_cliente);

    void detener_partida();

    bool esta_vacia();

    bool puedo_unir();

    bool esta_jugando();
};

#endif
