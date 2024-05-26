#ifndef LOBBY_ENVIADOR_H
#define LOBBY_ENVIADOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include <atomic>
#include <vector>
#include <list>

class LobbyEnviador : public Thread {
private:
    Socket *socket;

    Queue<std::vector<char>> *cola_enviador;

    std::atomic<bool> &sigo_hablando;

public:
    LobbyEnviador(Socket *socket, std::atomic<bool> &sigo_hablando,
                  Queue<std::vector<char>> *cola_enviador);

    void run() override;

    void kill() override;

    bool still_alive() override;
};

#endif
