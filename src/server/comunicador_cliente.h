#ifndef PALYER_H
#define PALYER_H

#include <atomic>
#include <list>
#include <memory>
#include <vector>

#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "enviador_cliente.h"
#include "gestor_partidas.h"
#include "recibidor_cliente.h"

class ComunicadorCliente {
private:
    int32_t id_cliente;

    Socket* skt_cliente;

    Queue<std::shared_ptr<SnapshotDTO>> cola_cliente;

    GestorPartidas* gestor_partidas;

    EnviadorCliente enviador_cliente;

    RecibidorCliente recibidor_cliente;

    std::atomic<bool> sigo_en_partida;

public:
    ComunicadorCliente(Socket* socket, GestorPartidas* gestor_partidas, int32_t id_cliente);

    void limpiar_cliente();

    void matar_cliente();

    [[nodiscard]] bool sigue_en_partida() const;

    void iniciar_cliente();
};

#endif
