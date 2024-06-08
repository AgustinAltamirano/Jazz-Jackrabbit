#include "servidor_deserializador.h"

#include <exception>
#include <iostream>

#include <arpa/inet.h>

#include "../common/tipo_personaje.h"

ServidorDeserializador::ServidorDeserializador(Socket* socket): socket(socket) {}

ComandoDTO* ServidorDeserializador::obtener_comando(bool* cerrado, int32_t& id_cliente) {
    char code = 0;
    socket->recvall(&code, 1, cerrado);
    if (*cerrado) {
        throw std::runtime_error("Se cerro el socket esperando una instruccion");
    }
    TipoComando comando = static_cast<TipoComando>(code);
    switch (comando) {
        case CREAR:
            return (deserializar_crear(cerrado, id_cliente));
            break;
        case UNIR:
            return (deserializar_unir(cerrado, id_cliente));
            break;
        case COMENZAR:
            return (deserializar_comenzar(cerrado, id_cliente));
            break;
        default:
            throw std::invalid_argument("no se encontro el caso en el deserializador del servidor");
    }
}

ComandoCrearDTO* ServidorDeserializador::deserializar_crear(bool* cerrado, int32_t& id_cliente) {
    uint8_t len_nombre = 0;
    socket->recvall(&len_nombre, 1, cerrado);
    std::vector<char> buffer(len_nombre);
    socket->recvall(buffer.data(), len_nombre, cerrado);
    TipoPersonaje personaje;
    int8_t capacidad_partida;
    socket->recvall(&personaje, 1, cerrado);
    socket->recvall(&capacidad_partida, 1, cerrado);
    ComandoCrearDTO* crear_dto = new ComandoCrearDTO(
            id_cliente, std::string(buffer.begin(), buffer.end()), personaje, capacidad_partida);
    return crear_dto;
}

ComandoUnirDTO* ServidorDeserializador::deserializar_unir(bool* cerrado,
                                                          const int32_t& id_cliente) {
    TipoPersonaje personaje;
    socket->recvall(&personaje, 1, cerrado);
    int32_t codigo_partida;
    socket->recvall(&codigo_partida, sizeof(int32_t), cerrado);
    codigo_partida = ntohl(codigo_partida);
    ComandoUnirDTO* unir_dto = new ComandoUnirDTO(id_cliente, codigo_partida, personaje);
    return unir_dto;
}

ComandoDTO* ServidorDeserializador::deserializar_comenzar(bool* cerrado, int32_t& id_cliente) {
    ComandoDTO* comando_dto = new ComandoDTO(id_cliente, COMENZAR);
    return comando_dto;
}
