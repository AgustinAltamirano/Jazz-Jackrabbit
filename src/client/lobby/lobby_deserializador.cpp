#include "lobby_deserializador.h"

#include <iostream>

#include <arpa/inet.h>

LobbyDeserializador::LobbyDeserializador(Socket* socket): socket(socket) {}

ComandoDTO* LobbyDeserializador::obtener_comando(bool* cerrado) {
    char codigo_comando = 0;
    socket->recvall(&codigo_comando, 1, cerrado);
    if (*cerrado) {
        throw std::runtime_error("Se cerro el socket esperando un comando");
    }
    TipoComando tipo_comando = static_cast<TipoComando>(codigo_comando);
    switch (tipo_comando) {
        case CREAR:
            return (deserializar_crear_partida(cerrado));
            break;
        case UNIR:
            return (deserializar_unir_partida(cerrado));
            break;
        default:
            throw std::invalid_argument("no se encontro el caso en el deserializador del servidor");
    }
}

ComandoCrearDTO* LobbyDeserializador::deserializar_crear_partida(bool* cerrado) {
    int32_t codigo_partida;
    socket->recvall(&codigo_partida, 4, cerrado);
    codigo_partida = ntohl(codigo_partida);
    ComandoCrearDTO* crear_dto = new ComandoCrearDTO(codigo_partida);
    return crear_dto;
}

ComandoUnirDTO* LobbyDeserializador::deserializar_unir_partida(bool* cerrado) {
    bool unio;
    socket->recvall(&unio, 1, cerrado);
    ComandoUnirDTO* unir_dto = new ComandoUnirDTO(unio);
    return unir_dto;
}
