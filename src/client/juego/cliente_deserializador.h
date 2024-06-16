#ifndef CLIENTE_DESERIALIZADOR_H
#define CLIENTE_DESERIALIZADOR_H

#include <memory>
#include <string>
#include <vector>

#include "../../common/snapshot_dto.h"
#include "../../common/socket.h"
#include "../../common/tipo_comando.h"

class ClienteDeserializador {
private:
    Socket* socket;

public:
    explicit ClienteDeserializador(Socket* socket);

    std::shared_ptr<SnapshotDTO> deserializar_snapshot_dto();
};

#endif
