#include "lobby_serializador.h"

#include <iostream>

#include <arpa/inet.h>

#include "../../common/tipo_comando.h"

std::vector<char> LobbySerializador::serializar_crear_partida(const std::string& nombre_escenario,
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

std::vector<char> LobbySerializador::serializar_unir_partida(const int32_t& codigo_partida,
                                                             const TipoPersonaje& personaje) {
    std::vector<char> buffer;
    buffer.push_back(UNIR);
    buffer.push_back(personaje);
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
