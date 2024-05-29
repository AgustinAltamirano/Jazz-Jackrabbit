#ifndef CLIENTE_RECIBIDOR_H
#define CLIENTE_RECIBIDOR_H

#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../../common/snapshot_dto.h"
#include "cliente_deserializador.h"

#include <atomic>
#include <vector>
#include <list>

class ClienteRecibidor : public Thread {
private:
    Queue<SnapshotDTO> *cola_recibidor;

    std::atomic<bool> &hablando;

    ClienteDeserializador cliente_deserializador;

public:
    ClienteRecibidor(Socket *socket, std::atomic<bool> &hablando, Queue<SnapshotDTO> *cola_recibidor);

    void run() override;

    void kill() override;

    bool still_alive() override;
};

#endif
