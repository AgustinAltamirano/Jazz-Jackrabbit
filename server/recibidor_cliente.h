#ifndef RECIBIDOR_CLIENTE_H_
#define RECIBIDOR_CLIENTE_H_


#include <atomic>
#include "../common/thread.h"
#include "servidor_protocolo.h"

class RecibidorCliente : public Thread {
private:
    ProtocoloServidor &protocolo;
    std::atomic<bool> sigo_vivo{true};

public:
    explicit RecibidorCliente(ProtocoloServidor &protocolo);

    void run() override;

    bool sigue_vivo() override;

    void kill() override;

    RecibidorCliente(const RecibidorCliente &) = delete;

    RecibidorCliente &operator=(const RecibidorCliente &) = delete;
};


#endif  // RECIBIDOR_CLIENTE_H_
