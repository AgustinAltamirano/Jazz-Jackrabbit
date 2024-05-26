#include "cliente_serializador.h"
#include "../common/tipo_comando.h"

std::vector<char> ClienteSerializador::serializar_comenzar_jugar() {
    std::vector<char> buffer;
    buffer.push_back(COMENZAR);
    return buffer;
}
