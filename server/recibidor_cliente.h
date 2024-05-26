#ifndef RECIBIDOR_CLIENTE_H_
#define RECIBIDOR_CLIENTE_H_


#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include "servidor_deserializador.h"
#include "gestor_partidas.h"

class Cliente;

#include <atomic>
#include <vector>
#include <list>

class RecibidorCliente : public Thread {
private:

    Queue<ComandoDTO *> *cola_recibidor;

    std::atomic<bool> &sigo_en_partida;

    std::atomic<bool> &sigo_jugando;

    ServidorDeserializador servidor_deserializador;

    Queue<SnapshotDTO> &cola_enviador;

    int32_t id_cliente;

public:
    RecibidorCliente(Socket *socket, std::atomic<bool> &sigo_en_partida,
                     std::atomic<bool> &sigo_jugando, int32_t &id_cliente,
                     Queue<SnapshotDTO> &cola_enviador);

    void run() override;

    void kill() override;

    bool still_alive() override;

    void establecer_cola_recibidor(Queue<ComandoDTO *> *cola_recibidor);
};


#endif  // RECIBIDOR_CLIENTE_H_
