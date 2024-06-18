#ifndef RECIBIDOR_CLIENTE_H_
#define RECIBIDOR_CLIENTE_H_


#include <atomic>
#include <list>
#include <vector>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "gestor_partidas.h"
#include "servidor_deserializador.h"
#include "servidor_serializador.h"

class Cliente;


class RecibidorCliente: public Thread {
private:
    int32_t id_cliente;

    std::atomic<bool>& sigo_en_partida;

    ServidorDeserializador servidor_deserializador;

    GestorPartidas* gestor_partidas;

    ServidorSerializador servidor_serializador;

    Queue<ComandoDTO*>* cola_recibidor;

    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador;

    bool cerrado = false;

public:
    RecibidorCliente(Socket* socket, std::atomic<bool>& sigo_en_partida, int32_t& id_cliente,
                     GestorPartidas* gestor_partidas,
                     Queue<std::shared_ptr<SnapshotDTO>>& cola_cliente);

    void run() override;

    void establecer_cola_recibidor(Queue<ComandoDTO*>* cola_recibidor);

    void inicio_recibidor_cliente();
};


#endif  // RECIBIDOR_CLIENTE_H_
