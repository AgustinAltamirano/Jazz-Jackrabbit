#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../../common/snapshot_dto.h"
#include "../../common/socket.h"
#include "../../common/tipo_comando.h"

class ClienteProtocolo {
private:
    SocketAbstracto* socket;

    std::vector<char> serializar_comando(const TipoComando& comando);

public:
    explicit ClienteProtocolo(SocketAbstracto* socket);

    void enviar_comando(TipoComando comando, bool* cerrado);

    std::shared_ptr<SnapshotDTO> recibir_snapshot_dto(bool* cerrado);
};

#endif
