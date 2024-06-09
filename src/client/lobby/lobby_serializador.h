#ifndef LOBBY_SERIALIZADOR_H
#define LOBBY_SERIALIZADOR_H

#include <string>
#include <vector>

#include "../../common/tipo_escenario.h"
#include "../../common/tipo_personaje.h"

class LobbySerializador {
private:
public:
    std::vector<char> serializar_crear_partida(const std::string& nombre_escenario, const TipoPersonaje& personaje,
                                               const int8_t& capacidad_partida);

    std::vector<char> serializar_unir_partida(const int32_t& codigo_partida, const TipoPersonaje& personaje);

    std::vector<char> serializar_comenzar_jugar();
};

#endif
