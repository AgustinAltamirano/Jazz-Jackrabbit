#ifndef CLIENTE_SERIALIZADOR_H
#define CLIENTE_SERIALIZADOR_H

#include <vector>
#include <string>
#include <cstdint>

class ClienteSerializador {
public:
    std::vector<char> serializar_comenzar_jugar();
};

#endif
