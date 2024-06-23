#ifndef LOBBY_ENVIADOR_H
#define LOBBY_ENVIADOR_H

#include <atomic>
#include <list>
#include <vector>

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "lobby_protocolo.h"

class LobbyEnviador: public Thread {
private:
    Socket* socket;

    Queue<std::shared_ptr<ComandoDTO>>* cola_enviador;

    std::atomic<bool>& sigo_hablando;

    LobbyProtocolo lobby_protocolo;

public:
    LobbyEnviador(Socket* socket, std::atomic<bool>& sigo_hablando,
                  Queue<std::shared_ptr<ComandoDTO>>* cola_enviador);

    void run() override;

    void stop() override;
};

#endif
