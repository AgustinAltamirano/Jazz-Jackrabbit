#ifndef PARTIDA_H
#define PARTIDA_H

#include <atomic>
#include <map>
#include <memory>
#include <string>

#include "../common/queue.h"
#include "../common/snapshot_dto.h"
#include "../common/thread.h"

class ComandoServer;


class Partida: public Thread {
private:
    std::map<int, TipoPersonaje> mapa_clientes_juego;

    std::map<int, Queue<std::shared_ptr<SnapshotDTO>>*> cola_snapshots;

    int32_t codigo_partida;

    std::string nombre_escenario;

    Queue<ComandoServer*> cola_comandos;

    std::atomic<bool> sigo_jugando;

    int cantidad_jugadores;

    std::atomic<bool> comenzada;

    int8_t capacidad_partida;

    bool borrar_cliente_mapa(int32_t& id_cliente);

    bool borrar_cliente_snapshots(int32_t& id_cliente);

public:
    Partida(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador, int32_t codigo_partida,
            std::string& nombre_escenario, const int32_t& id_cliente, TipoPersonaje& personaje,
            const int8_t& capacidad_partida);

    void run() override;

    void stop() override;

    Queue<ComandoServer*>* obtener_comandos();

    void agregar_cliente(Queue<std::shared_ptr<SnapshotDTO>>* cola_enviador,
                         const int32_t& id_cliente, const TipoPersonaje& personaje);

    bool comparar_codigo_partida(const int32_t& codigo_a_comparar);

    int32_t obtener_codigo_partida();

    bool borrar_cliente(int32_t& id_cliente);

    void detener_partida();

    bool esta_vacia();

    bool no_esta_comenzada();

    bool esta_jugando();

    ~Partida() override;
};

#endif
