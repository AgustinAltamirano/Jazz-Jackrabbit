#ifndef ENVIADOR_CLIENTE_H
#define ENVIADOR_CLIENTE_H

#include <atomic>
#include <vector>

#include "../client/juego/cliente_recibidor.h"
#include "../common/comando_dto.h"
#include "../common/queue.h"
#include "../common/snapshot_dto.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/tipo_comando.h"

#include "gestor_partidas.h"
#include "recibidor_cliente.h"
#include "servidor_deserializador.h"
#include "servidor_serializador.h"

class EnviadorCliente: public Thread {
private:
    ServidorSerializador servidor_serializador;

    ServidorDeserializador servidor_deserializador;

    Socket* skt_cliente;

    std::atomic<bool>& sigo_en_partida;

    bool cerrado = false;

    Queue<std::shared_ptr<SnapshotDTO>> cola_enviador;

    // El EnviadorCliente se encargara de lanzarlo y manejarlo debido a que al principio tenemos una
    // parte sincronica.
    RecibidorCliente recibidor_cliente;

    Queue<ComandoDTO*>* cola_recibidor;

    GestorPartidas* gestor_partidas;

    int32_t id_cliente;

public:
    EnviadorCliente(Socket* skt_cliente, std::atomic<bool>& sigo_en_partida,
                    GestorPartidas* gestor_partidas, int32_t& id_cliente);

    void run() override;

    void stop() override;

    void join_recibidor_cliente();

    void inicio_recibidor_cliente();

    void cerrar_cola();
};

#endif
