#ifndef CLIENTE_RECIBIDOR_H
#define CLIENTE_RECIBIDOR_H

#include <atomic>
#include <list>
#include <vector>

#include "../../common/queue.h"
#include "../../common/snapshot_dto.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "cliente_protocolo.h"

class ClienteRecibidor: public Thread {
private:
    Queue<std::shared_ptr<SnapshotDTO>>* cola_recibidor;

    std::atomic<bool>& hablando;

    ClienteProtocolo cliente_protocolo;

    Socket* skt_cliente;

public:
    ClienteRecibidor(Socket* socket, std::atomic<bool>& hablando,
                     Queue<std::shared_ptr<SnapshotDTO>>* cola_recibidor);

    void run() override;

    void stop() override;
};

#endif
