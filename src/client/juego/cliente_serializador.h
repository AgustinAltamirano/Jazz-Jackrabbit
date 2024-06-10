#ifndef CLIENTE_SERIALIZADOR_H
#define CLIENTE_SERIALIZADOR_H

#include <cstdint>
#include <string>
#include <vector>

#include "../../common/tipo_comando.h"

class ClienteSerializador {
public:
    std::vector<char> serializar_comando(const TipoComando& comando);
};

#endif
