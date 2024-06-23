#ifndef ENVIADOR_CLIENTE_H
#define ENVIADOR_CLIENTE_H

#include <atomic>
#include <memory>
#include <vector>

#include "../client/juego/cliente_recibidor.h"
#include "../common/queue.h"
#include "../common/snapshot_dto.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/tipo_comando.h"
#include "src/client/lobby/comando_dto.h"

#include "gestor_partidas.h"
#include "recibidor_cliente.h"

class EnviadorCliente: public Thread {
private:
    ServidorProtocolo servidor_protocolo;

    std::atomic<bool>& sigo_en_partida;

    bool cerrado = false;

    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador;

    int32_t id_cliente;

public:
    EnviadorCliente(Socket* skt_cliente, std::atomic<bool>& sigo_en_partida,
                    const int32_t& id_cliente, Queue<std::shared_ptr<SnapshotDTO>>& cola_cliente);

    void run() override;

    void stop() override;

    void cerrar_cola();
};

#endif
