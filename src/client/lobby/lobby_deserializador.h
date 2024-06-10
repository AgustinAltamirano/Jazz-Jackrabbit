#ifndef LOBBY_DESERIALIZADOR_H
#define LOBBY_DESERIALIZADOR_H

#include <string>
#include <vector>

#include "../../common/comando_comenzar_dto.h"
#include "../../common/comando_crear_dto.h"
#include "../../common/comando_dto.h"
#include "../../common/comando_unir_dto.h"
#include "../../common/socket.h"

class LobbyDeserializador {
private:
    Socket* socket;

public:
    explicit LobbyDeserializador(Socket* socket);

    ComandoDTO* obtener_comando(bool* cerrado);

    ComandoCrearDTO* deserializar_crear_partida(bool* cerrado);

    ComandoUnirDTO* deserializar_unir_partida(bool* cerrado);
};

#endif
