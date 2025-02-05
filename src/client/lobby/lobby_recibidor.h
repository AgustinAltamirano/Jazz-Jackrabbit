#ifndef LOBBY_RECIBIDOR_H
#define LOBBY_RECIBIDOR_H

#include <atomic>
#include <list>
#include <vector>

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "comando_dto.h"
#include "lobby_protocolo.h"

class LobbyRecibidor: public Thread {
private:
    Queue<std::shared_ptr<ComandoDTO>>* cola_recibidor;

    std::atomic<bool>& sigo_hablando;

    LobbyProtocolo lobby_protocolo;

public:
    LobbyRecibidor(Socket* socket, std::atomic<bool>& sigo_hablando,
                   Queue<std::shared_ptr<ComandoDTO>>* cola_recibidor);

    void run() override;

    void stop() override;
};

#endif
