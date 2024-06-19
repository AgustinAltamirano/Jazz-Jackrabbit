#include "lobby_protocolo.h"

#include <iostream>

#include <arpa/inet.h>

#include "../../common/tipo_comando.h"

LobbyProtocolo::LobbyProtocolo(Socket* socket): socket(socket) {}

std::vector<char> LobbyProtocolo::serializar_crear_partida(const std::string& nombre_escenario,
                                                           const TipoPersonaje& personaje,
                                                           const int8_t& capacidad_partida) {
    std::vector<char> buffer;
    uint8_t len_nombre = nombre_escenario.length();
    buffer.push_back(CREAR);
    buffer.push_back(len_nombre);
    buffer.insert(buffer.end(), nombre_escenario.begin(), nombre_escenario.end());
    buffer.push_back(personaje);
    buffer.push_back(capacidad_partida);
    return buffer;
}

std::vector<char> LobbyProtocolo::serializar_unir_partida(const int32_t& codigo_partida,
                                                          const TipoPersonaje& personaje) {
    std::vector<char> buffer;
    buffer.push_back(UNIR);
    buffer.push_back(personaje);
    int32_t codigo_partida_transformado = htonl(codigo_partida);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> LobbyProtocolo::serializar_validar_escenario(
        const std::string& nombre_escenario) {
    std::vector<char> buffer;
    uint8_t len_nombre = nombre_escenario.length();
    buffer.push_back(VALIDAR_ESCENARIO);
    buffer.push_back(len_nombre);
    buffer.insert(buffer.end(), nombre_escenario.begin(), nombre_escenario.end());
    return buffer;
}

ComandoDTO* LobbyProtocolo::obtener_comando(bool* cerrado) {
    char codigo_comando = 0;
    socket->recvall(&codigo_comando, 1, cerrado);
    if (*cerrado) {
        throw std::runtime_error("Se cerro el socket esperando un comando");
    }
    TipoComando tipo_comando = static_cast<TipoComando>(codigo_comando);
    switch (tipo_comando) {
        case CREAR:
            return (deserializar_crear_partida(cerrado));
        case UNIR:
            return (deserializar_unir_partida(cerrado));
        case VALIDAR_ESCENARIO:
            return (deserializar_validar_escenario(cerrado));
        default:
            std::cout << "ERROR de comando";
            throw std::invalid_argument("no se encontro el caso en el deserializador del servidor");
    }
}

ComandoCrearDTO* LobbyProtocolo::deserializar_crear_partida(bool* cerrado) {
    int32_t codigo_partida;
    socket->recvall(&codigo_partida, 4, cerrado);
    codigo_partida = ntohl(codigo_partida);
    ComandoCrearDTO* crear_dto = new ComandoCrearDTO(codigo_partida);
    *cerrado = true;
    return crear_dto;
}

ComandoUnirDTO* LobbyProtocolo::deserializar_unir_partida(bool* cerrado) {
    bool unio;
    socket->recvall(&unio, 1, cerrado);
    ComandoUnirDTO* unir_dto = new ComandoUnirDTO(unio);
    *cerrado = true;
    return unir_dto;
}

ComandoValidarDTO* LobbyProtocolo::deserializar_validar_escenario(bool* cerrado) {
    bool es_valida;
    socket->recvall(&es_valida, 1, cerrado);
    ComandoValidarDTO* validar_dto = new ComandoValidarDTO(es_valida);
    return validar_dto;
}

int32_t LobbyProtocolo::obtener_id_cliente() {
    int32_t id_cliente;
    bool cerrado = false;
    socket->recvall(&id_cliente, sizeof(int), &cerrado);
    id_cliente = ntohl(id_cliente);
    return id_cliente;
}

void LobbyProtocolo::enviar_comando(std::vector<char> bytes, bool* cerrado) {
    socket->sendall(bytes.data(), bytes.size(), cerrado);
}
