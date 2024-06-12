#ifndef RECIBIDOR_CLIENTE_H_
#define RECIBIDOR_CLIENTE_H_


#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "gestor_partidas.h"
#include "servidor_deserializador.h"

class Cliente;

#include <atomic>
#include <list>
#include <vector>

class RecibidorCliente: public Thread {
private:
    Queue<ComandoDTO*>* cola_recibidor;

    std::atomic<bool>& sigo_en_partida;

    std::atomic<bool>& sigo_jugando;

    ServidorDeserializador servidor_deserializador;

    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador;

    int32_t id_cliente;

public:
    RecibidorCliente(Socket* socket, std::atomic<bool>& sigo_en_partida,
                     std::atomic<bool>& sigo_jugando, int32_t& id_cliente,
                     Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador);

    void run() override;

    void stop() override;

    void establecer_cola_recibidor(Queue<ComandoDTO*>* cola_recibidor);
};


#endif  // RECIBIDOR_CLIENTE_H_
