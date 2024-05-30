#ifndef LOBBY_DESERIALIZADOR_H
#define LOBBY_DESERIALIZADOR_H

#include "../../common/comando_dto.h"
#include "../../common/comando_crear_dto.h"
#include "../../common/comando_unir_dto.h"
#include "../../common/comando_comenzar_dto.h"
#include "../../common/socket.h"

#include <vector>
#include <string>

class LobbyDeserializador {
private:
    Socket *socket;

public:
    explicit LobbyDeserializador(Socket *socket);

    ComandoDTO *obtener_comando(bool *cerrado);

    ComandoCrearDTO *deserializar_crear_partida(bool *cerrado);

    ComandoUnirDTO *deserializar_unir_partida(bool *cerrado);

    ComandoComenzarDTO *deserializar_comenzar_juego(bool *cerrado);
};

#endif
