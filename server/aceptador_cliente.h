#ifndef ACEPTADOR_CLIENTE_H_
#define ACEPTADOR_CLIENTE_H_

#include <vector>
#include <atomic>
#include <string>
#include "../common/thread.h"
#include "../common/socket.h"
#include "monitor_partidas.h"

class AceptadorCliente : public Thread {
private:
    Socket skt_escuchador;
    std::atomic<bool> sigo_vivo{true};
    std::vector<Thread *> threads;

    void manejar_cliente(Socket skt_cliente,
                         MonitorPartidas &monitor_partidas);

    void limpiar_clientes();

    void eliminar_todos_clientes();

    bool sigue_vivo() override;

public:
    explicit AceptadorCliente(std::string
    &servname);

    void run() override;

    void kill() override;

    AceptadorCliente(const AceptadorCliente &) = delete;

    AceptadorCliente &operator=(const AceptadorCliente &) = delete;
};

#endif  // ACEPTADOR_CLIENTE_H_
