#ifndef LOBBY_SERIALIZADOR_H
#define LOBBY_SERIALIZADOR_H

#include <vector>
#include <string>

class LobbySerializador {
private:
public:

    std::vector<char> serializar_crear_partida(const int8_t &capacidad_partida);

    std::vector<char> serializar_unir_partida(const int32_t &codigo_partida);

    std::vector<char> serializar_comenzar_jugar();
};

#endif
