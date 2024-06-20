#ifndef CLIENTE_ENVIADOR_H
#define CLIENTE_ENVIADOR_H

#include <atomic>
#include <list>
#include <vector>

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "cliente_protocolo.h"

class ClienteEnviador: public Thread {
private:
    Socket* socket;

    Queue<TipoComando>* cola_enviador;

    ClienteProtocolo cliente_protocolo;

    std::atomic<bool>& hablando;

public:
    ClienteEnviador(Socket* socket, std::atomic<bool>& hablando, Queue<TipoComando>* cola_enviador);

    void run() override;

    void stop() override;
};

#endif
