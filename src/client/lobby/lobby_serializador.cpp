#include "lobby_serializador.h"

#include <iostream>

#include <arpa/inet.h>

#include "../../common/tipo_comando.h"

std::vector<char> LobbySerializador::serializar_crear_partida(const int8_t& capacidad_partida) {
    std::vector<char> buffer;
    buffer.push_back(CREAR);
    buffer.push_back(capacidad_partida);
    return buffer;
}

std::vector<char> LobbySerializador::serializar_unir_partida(const int32_t& codigo_partida) {
    std::vector<char> buffer;
    buffer.push_back(UNIR);
    int32_t codigo_partida_transformado = htonl(codigo_partida);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> LobbySerializador::serializar_comenzar_jugar() {
    std::vector<char> buffer;
    buffer.push_back(COMENZAR);
    return buffer;
}
