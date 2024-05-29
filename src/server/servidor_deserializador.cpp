#include "servidor_deserializador.h"
#include <exception>
#include <iostream>
#include <arpa/inet.h>

ServidorDeserializador::ServidorDeserializador(Socket *socket) : socket(socket) {}

ComandoDTO *ServidorDeserializador::obtener_comando(bool *cerrado, int32_t &id_cliente) {
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
    }
}

ComandoCrearDTO *ServidorDeserializador::deserializar_crear(bool *cerrado, int32_t &id_cliente) {
    int8_t capacidad_partida;
    socket->recvall(&capacidad_partida, 1, cerrado);
    ComandoCrearDTO *crear_dto = new ComandoCrearDTO(id_cliente, capacidad_partida);
    return crear_dto;
}

ComandoUnirDTO *ServidorDeserializador::deserializar_unir(bool *cerrado, int32_t &id_cliente) {
    int32_t codigo_partida;
    socket->recvall(&codigo_partida, sizeof(int32_t), cerrado);
    codigo_partida = ntohl(codigo_partida);
    ComandoUnirDTO *unir_dto = new ComandoUnirDTO(id_cliente, codigo_partida);
    return unir_dto;
}

ComandoDTO *ServidorDeserializador::deserializar_comenzar(bool *cerrado, int32_t &id_cliente) {
    ComandoDTO *comando_dto = new ComandoDTO(id_cliente, COMENZAR);
    return comando_dto;
}

