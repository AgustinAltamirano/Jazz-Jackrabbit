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

    std::string nombre_escenario;

    Queue<ComandoDTO*> cola_comandos;

    bool sigo_jugando;

    bool admite_jugadores;

    int8_t capacidad_partida;

public:
    Partida(Queue<SnapshotDTO>* cola_enviador, int32_t& codigo_partida,
            std::string& nombre_escenario, const int32_t& id_cliente, TipoPersonaje& personaje,
            int8_t& capacidad_partida);

    void run() override;

    void stop() override;

    Queue<ComandoDTO*>* obtener_comandos();

    void agregar_cliente(Queue<SnapshotDTO>* cola_enviador, const int32_t& id_cliente, const TipoPersonaje& personaje);

    bool comparar_codigo_partida(const int32_t& codigo_a_comparar);

    int32_t obtener_codigo_partida();

    bool comparar_nombre_escenario(const std::string& nombre_escenario);

    bool borrar_cliente(int32_t& id_cliente);

    void detener_partida();

    bool esta_vacia();

    bool puedo_unir();

    bool esta_jugando();
};

#endif
