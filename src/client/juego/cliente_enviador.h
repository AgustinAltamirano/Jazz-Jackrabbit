#ifndef CLIENTE_ENVIADOR_H
#define CLIENTE_ENVIADOR_H

#include <atomic>
#include <list>
#include <vector>

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

class ClienteEnviador: public Thread {
private:
    Socket* socket;

    Queue<std::vector<char>>* cola_enviador;

    std::atomic<bool>& hablando;

public:
    ClienteEnviador(Socket* socket, std::atomic<bool>& hablando,
                    Queue<std::vector<char>>* cola_enviador);

    void run() override;

    void stop() override;
};

#endif
