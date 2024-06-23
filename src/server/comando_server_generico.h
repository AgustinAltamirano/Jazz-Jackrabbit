#ifndef COMANDO_SERVER_GENERICO_H
#define COMANDO_SERVER_GENERICO_H

#include <cstdint>
#include <vector>

#include "../common/queue.h"
#include "../common/snapshot_dto.h"
#include "../common/tipo_comando.h"

#include "gestor_partidas.h"
#include "servidor_protocolo.h"
#include "comando_server.h"


class ComandoServerGenerico : public ComandoServer {
public:
    ComandoServerGenerico(int32_t& id_cliente, TipoComando comando);

    Queue<std::shared_ptr<ComandoServer>>* ejecutar(GestorPartidas* gestor_partidas,
                                    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                    bool& cerrado,
                                    ServidorProtocolo& servidor_serializador) override;
};

#endif
