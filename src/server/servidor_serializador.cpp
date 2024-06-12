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

std::vector<char> ServidorSerializador::serializar_id_cliente(const int32_t& id_cliente) {
    std::vector<char> buffer;
    int32_t id_cliente_transformado = htonl(id_cliente);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&id_cliente_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServidorSerializador::serializar_snapshot(SnapshotDTO snapshot_dto) {
    std::vector<ClienteDTO> clientes_dto = snapshot_dto.obtener_clientes();
    std::vector<BloqueEscenarioDTO> bloques_dto = snapshot_dto.obtener_bloques_escenario();

    uint8_t num_clientes = clientes_dto.size();
    uint8_t num_bloques = bloques_dto.size();

    std::vector<char> buffer;
    buffer.reserve(4 + (sizeof(ClienteDTO) * num_clientes) +
                   sizeof(BloqueEscenarioDTO) * num_bloques);

    buffer.push_back(static_cast<char>(num_clientes));
    buffer.push_back(static_cast<char>(num_bloques));
    buffer.push_back(snapshot_dto.obtener_tipo_escenario());
    buffer.push_back(snapshot_dto.es_fin_juego());

    for (const auto& obj: clientes_dto) {
        int32_t id_cliente_transformado = htonl(obj.id_cliente);
        unsigned char const* p = reinterpret_cast<unsigned char const*>(&id_cliente_transformado);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        buffer.push_back(obj.tipo_personaje);

        int32_t posicion_transformada_x = htonl(obj.pos_x);
        p = reinterpret_cast<unsigned char const*>(&posicion_transformada_x);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        int32_t posicion_transformada_y = htonl(obj.pos_y);
        p = reinterpret_cast<unsigned char const*>(&posicion_transformada_y);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        buffer.push_back(obj.de_espaldas);

        buffer.push_back(obj.estado);

        int32_t vida_transformada = htonl(obj.vida);
        p = reinterpret_cast<unsigned char const*>(&vida_transformada);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        int32_t puntos_transformados = htonl(obj.puntos);
        p = reinterpret_cast<unsigned char const*>(&puntos_transformados);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        buffer.push_back(obj.arma_actual);

        int32_t balas_restantes_transformadas = htonl(obj.balas_restantes);
        p = reinterpret_cast<unsigned char const*>(&balas_restantes_transformadas);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    }

    for (const auto& obj: bloques_dto) {
        int32_t posicion_transformada_x = htonl(obj.pos_x);
        unsigned char const* p = reinterpret_cast<unsigned char const*>(&posicion_transformada_x);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        int32_t posicion_transformada_y = htonl(obj.pos_y);
        p = reinterpret_cast<unsigned char const*>(&posicion_transformada_y);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        int32_t angulo_transformado = htonl(obj.angulo);
        p = reinterpret_cast<unsigned char const*>(&angulo_transformado);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        uint32_t ancho_transformado = htonl(obj.ancho);
        p = reinterpret_cast<unsigned char const*>(&ancho_transformado);
        buffer.insert(buffer.end(), p, p + sizeof(uint32_t));

        uint32_t alto_transformado = htonl(obj.ancho);
        p = reinterpret_cast<unsigned char const*>(&alto_transformado);
        buffer.insert(buffer.end(), p, p + sizeof(uint32_t));

        buffer.push_back(obj.tipo);
    }

    return buffer;
}
