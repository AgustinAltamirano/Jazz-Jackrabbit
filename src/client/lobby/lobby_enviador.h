#ifndef LOBBY_ENVIADOR_H
#define LOBBY_ENVIADOR_H

#include <atomic>
#include <list>
#include <vector>

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

class LobbyEnviador: public Thread {
private:
    Socket* socket;

    Queue<std::vector<char>>* cola_enviador;

    std::atomic<bool>& sigo_hablando;

public:
    LobbyEnviador(Socket* socket, std::atomic<bool>& sigo_hablando,
                  Queue<std::vector<char>>* cola_enviador);

    void run() override;

    void stop() override;
};

#endif
