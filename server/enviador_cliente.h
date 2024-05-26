#ifndef ENVIADOR_CLIENTE_H
#define ENVIADOR_CLIENTE_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include "recibidor_cliente.h"
#include "servidor_deserializador.h"
#include "servidor_serializador.h"
#include "../common/tipo_comando.h"
#include "../common/snapshot_dto.h"
#include "../client/cliente_recibidor.h"
#include "../common/comando_dto.h"
#include "gestor_partidas.h"

#include <atomic>
#include <vector>

class EnviadorCliente : public Thread {
private:
    ServidorSerializador servidor_serializador;

    ServidorDeserializador servidor_deserializador;

    std::atomic<bool> &sigo_en_partida;

    std::atomic<bool> &sigo_jugando;

    bool cerrado = false;

    Queue<SnapshotDTO> cola_enviador;

    // El EnviadorCliente se encargara de lanzarlo y manejarlo debido a que al principio tenemos una parte sincronica.
    RecibidorCliente recibidor_cliente;

    Queue<ComandoDTO *> *cola_recibidor;

    GestorPartidas *gestor_partidas;

    int32_t id_cliente;

public:
    EnviadorCliente(Socket
                    *skt_cliente,
                    std::atomic<bool> &sigo_en_partida, std::atomic<bool>
                    &sigo_jugando,
                    GestorPartidas *gestor_partidas, int32_t
                    &id_cliente);

    void run() override;

    void kill() override;

    bool still_alive() override;

    void join_recibidor_cliente();

    void inicio_recibidor_cliente();

    void cerrar_cola();
};

#endif
