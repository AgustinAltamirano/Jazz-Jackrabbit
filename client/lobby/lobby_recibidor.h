#ifndef LOBBY_RECIBIDOR_H
#define LOBBY_RECIBIDOR_H

#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../../common/comando_dto.h"
#include "lobby_deserializador.h"

#include <atomic>
#include <vector>
#include <list>

class LobbyRecibidor : public Thread {
private:
    Queue<ComandoDTO *> *cola_recibidor;

    std::atomic<bool> &sigo_hablando;

    LobbyDeserializador lobby_deserializador;

public:
    LobbyRecibidor(Socket *socket, std::atomic<bool> &sigo_hablando,
                   Queue<ComandoDTO *> *cola_recibidor);

    void run() override;

    void kill() override;

    bool still_alive() override;
};

#endif
