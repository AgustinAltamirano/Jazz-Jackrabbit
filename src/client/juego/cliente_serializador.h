#ifndef CLIENTE_SERIALIZADOR_H
#define CLIENTE_SERIALIZADOR_H

#include <cstdint>
#include <string>
#include <vector>

class ClienteSerializador {
public:
    std::vector<char> serializar_comenzar_jugar();
};

#endif
