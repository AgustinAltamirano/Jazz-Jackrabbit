#ifndef CLIENTE_DESERIALIZADOR_H
#define CLIENTE_DESERIALIZADOR_H

#include "../common/tipo_comando.h"
#include "../common/snapshot_dto.h"
#include "../common/socket.h"

#include <vector>
#include <string>

class ClienteDeserializador {
private:
    Socket *socket;

public:
    explicit ClienteDeserializador(Socket
                                   *socket);

    SnapshotDTO deserializar_juego_dto(bool *cerrado);
};

#endif
