#ifndef PALYER_H
#define PALYER_H

#include <atomic>
#include <list>
#include <vector>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "enviador_cliente.h"
#include "gestor_partidas.h"
#include "recibidor_cliente.h"

class ComunicadorCliente: public Thread {
private:
    int32_t id_cliente;

    Socket skt_cliente;

    EnviadorCliente enviador_cliente;

    std::atomic<bool> sigo_en_partida;

    std::atomic<bool> sigo_jugando;

public:
    ComunicadorCliente(Socket socket, GestorPartidas* gestor_partidas, int32_t id_cliente);

    void stop() override;

    void join();

    void run() override;
};

#endif
