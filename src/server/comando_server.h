#ifndef COMANDO_LOBBY_H
#define COMANDO_LOBBY_H

#include <cstdint>
#include <vector>

#include "../common/queue.h"
#include "../common/snapshot_dto.h"
#include "../common/tipo_comando.h"

#include "gestor_partidas.h"
#include "servidor_protocolo.h"


class ComandoServer {
private:
    TipoComando comando;
    int32_t id_cliente;

public:
    ComandoServer();

    explicit ComandoServer(TipoComando comando);

    ComandoServer(int32_t& id_cliente, TipoComando comando);

    TipoComando obtener_comando();

    virtual Queue<ComandoServer*>* ejecutar(GestorPartidas* gestor_partidas,
                                   Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                   int32_t id_cliente, bool& cerrado,
                                   ServidorProtocolo& servidor_serializador);

    int32_t obtener_id_cliente();

    virtual ~ComandoServer() = default;
};

#endif
