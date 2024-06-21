#include "servidor_protocolo_serializador.h"

#include <arpa/inet.h>

#include "common/tipo_comando.h"

ServidorProtocoloSerializador::ServidorProtocoloSerializador() {}

std::vector<char> ServidorProtocoloSerializador::serializar_crear_partida(
        const int32_t& codigo_partida) {
    std::vector<char> buffer;
    buffer.push_back(CREAR);
    int32_t codigo_partida_transformado = htonl(codigo_partida);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServidorProtocoloSerializador::serializar_error_crear_partida() {
    std::vector<char> buffer;
    buffer.push_back(CREAR);
    int32_t codigo_partida_transformado = htonl(-1);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServidorProtocoloSerializador::serializar_unir_partida(const bool& unir) {
    std::vector<char> buffer;
    buffer.push_back(UNIR);
    buffer.push_back(unir);
    return buffer;
}

std::vector<char> ServidorProtocoloSerializador::serializar_validar_escenario(
        const bool& es_valido) {
    std::vector<char> buffer;
    buffer.push_back(VALIDAR_ESCENARIO);
    buffer.push_back(es_valido);
    return buffer;
}

std::vector<char> ServidorProtocoloSerializador::serializar_id_cliente(const int32_t& id_cliente) {
    std::vector<char> buffer;
    int32_t id_cliente_transformado = htonl(id_cliente);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&id_cliente_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}
