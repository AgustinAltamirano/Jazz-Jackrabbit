#ifndef CLIENTE_PROTOCOLO_H
#define CLIENTE_PROTOCOLO_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../../common/tipo_comando.h"
#include "../../common/snapshot_dto.h"
#include "../../common/socket.h"

class ClienteProtocolo {
private:
    Socket* socket;

public:
    explicit ClienteProtocolo(Socket* socket);

    std::vector<char> serializar_comando(const TipoComando& comando);

    void enviar_comando(std::vector<char> bytes, bool* cerrado);

    std::shared_ptr<SnapshotDTO> recibir_snapshot_dto(bool* cerrado);
};

#endif
