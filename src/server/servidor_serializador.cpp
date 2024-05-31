#include "servidor_serializador.h"

#include <arpa/inet.h>


ServidorSerializador::ServidorSerializador() {}

ServidorSerializador::ServidorSerializador(Socket* socket): socket(socket) {}

void ServidorSerializador::enviar_crear_partida(const int32_t& codigo_partida, bool* cerrado) {
    std::vector<char> buffer = serializar_crear_partida(codigo_partida);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorSerializador::enviar_error_crear_partida(bool* cerrado) {
    std::vector<char> buffer = serializar_error_crear_partida();
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorSerializador::enviar_unir_partida(const bool& unir, bool* cerrado) {
    std::vector<char> buffer = serializar_unir_partida(unir);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorSerializador::enviar_iniciar_juego(const bool& iniciar, bool* cerrado) {
    std::vector<char> buffer = serializar_iniciar_juego(iniciar);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorSerializador::enviar_id_cliente(const int32_t& id_cliente, bool* cerrado) {
    std::vector<char> buffer = serializar_id_cliente(id_cliente);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorSerializador::enviar_snapshot(const SnapshotDTO& snapshot_dto, bool* cerrado) {
    std::vector<char> buffer = serializar_snapshot(snapshot_dto);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

std::vector<char> ServidorSerializador::serializar_crear_partida(const int32_t& codigo_partida) {
    std::vector<char> buffer;
    buffer.push_back(CREAR);
    int32_t codigo_partida_transformado = htonl(codigo_partida);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServidorSerializador::serializar_error_crear_partida() {
    std::vector<char> buffer;
    buffer.push_back(CREAR);
    int32_t codigo_partida_transformado = htonl(-1);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServidorSerializador::serializar_unir_partida(const bool& unir) {
    std::vector<char> buffer;
    buffer.push_back(UNIR);
    buffer.push_back(unir);
    return buffer;
}

std::vector<char> ServidorSerializador::serializar_iniciar_juego(const bool& iniciar) {
    std::vector<char> buffer;
    buffer.push_back(COMENZAR);
    buffer.push_back(iniciar);
    return buffer;
}

std::vector<char> ServidorSerializador::serializar_id_cliente(const int32_t& id_cliente) {
    std::vector<char> buffer;
    int32_t id_cliente_transformado = htonl(id_cliente);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&id_cliente_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServidorSerializador::serializar_snapshot(SnapshotDTO snapshot_dto) {
    std::vector<ClienteDTO> clientes_dto = snapshot_dto.obtener_clientes();

    uint8_t num_clientes = clientes_dto.size();

    std::vector<char> buffer;
    buffer.reserve(4 + (sizeof(ClienteDTO) * num_clientes));

    buffer.push_back(static_cast<char>(num_clientes));
    buffer.push_back(snapshot_dto.es_fin_juego());

    for (const auto& obj: clientes_dto) {
        int32_t id_cliente_transformado = htonl(obj.id_cliente);
        unsigned char const* p = reinterpret_cast<unsigned char const*>(&id_cliente_transformado);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    }
    return buffer;
}
