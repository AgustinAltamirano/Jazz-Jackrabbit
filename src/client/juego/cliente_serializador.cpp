#include "cliente_serializador.h"

#include "../../common/tipo_comando.h"

std::vector<char> ClienteSerializador::serializar_comando(const TipoComando& comando) {
    std::vector<char> buffer;
    buffer.push_back(comando);
    return buffer;
}
