#ifndef CLIENTE_SERIALIZADOR_H
#define CLIENTE_SERIALIZADOR_H

#include <cstdint>
#include <string>
#include <vector>

#include "../../common/tipo_comando.h"
#include "src/common/socket.h"

class ClienteSerializador {
private:
    Socket* socket;

public:
    explicit ClienteSerializador(Socket* socket);
    std::vector<char> serializar_comando(const TipoComando& comando);
    void enviar_comando(std::vector<char> bytes, bool* cerrado);
};

#endif
