#include <vector>
#include <netinet/in.h>
#include <iostream>
#include <utility>
#include <cstring>
#include "servidor_protocolo.h"
#include "../common/liberror.h"

#define SIZE_BUFF_INICIAL 3
#define CANT_BYTES_RESTANTES_JOIN 2
#define CANT_BYTES_CODIGO 4
#define INICIAR_PARTIDA 0X01
#define UNIR_PARTIDA 0X02
#define ENVIO_CLIENTE 0X03
#define RESPUESTA_SERVIDOR 0X04
#define EXITO 0
#define FRACASO 1

ProtocoloServidor::ProtocoloServidor(Socket skt_cliente,
                                     Juego &juego,
                                     Queue<std::string> &cola_cliente) :
        skt(std::move(skt_cliente)),
        juego(juego),
        cola_cliente(cola_cliente) {}

void ProtocoloServidor::recibir_mensaje_cliente(std::vector<char> &buffer) {
    buffer.resize((SIZE_BUFF_INICIAL));
    bool was_closed = false;
    skt.recvall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        sigo_vivo = false;
        return;
    }
    std::int16_t bytes_restantes = obtener_bytes_restantes(buffer);
    buffer.resize(SIZE_BUFF_INICIAL + bytes_restantes);
    skt.recvall(buffer.data() + SIZE_BUFF_INICIAL, bytes_restantes, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
        return;
    }
}

void ProtocoloServidor::enviar_codigo_partida(std::uint32_t codigo) {
    std::vector<char> buffer(CANT_BYTES_CODIGO);
    std::uint32_t *ptr = (std::uint32_t *) &buffer.at(0);
    *ptr = htonl(codigo);
    bool was_closed = false;
    skt.sendall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) sigo_vivo = false;
}

void
ProtocoloServidor::enviar_mensaje_confirmacion(std::uint8_t confirmacion) {
    std::vector<char> buffer(1);
    buffer[0] = confirmacion;
    bool was_closed = false;
    skt.sendall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) sigo_vivo = false;
}

void ProtocoloServidor::
convertir_endianness_join(const std::vector<char> &buffer_viejo,
                          std::vector<char> &buffer_nuevo) {
    std::uint32_t *ptr = (std::uint32_t *) &buffer_viejo.at(1);
    std::uint32_t *ptr_nuevo = (std::uint32_t *) &buffer_nuevo[1];
    *ptr_nuevo = ntohl(*ptr);
}

void ProtocoloServidor::enviar_mensaje() {
    std::string broadcast = cola_cliente.pop();
    std::vector<char> buffer_a_enviar;
    crear_mensaje_broadcast(buffer_a_enviar, broadcast);
    bool was_closed = false;
    skt.sendall(buffer_a_enviar.data(), buffer_a_enviar.size(), &was_closed);
    if (was_closed) sigo_vivo = false;
}

void ProtocoloServidor::recibir_mensaje() {
    std::vector<char> buffer;
    recibir_mensaje_cliente(buffer);
    realizar_accion(buffer);
}

std::int16_t ProtocoloServidor::
obtener_bytes_restantes(std::vector<char> &buffer) {
    if (buffer[0] == INICIAR_PARTIDA || buffer[0] == ENVIO_CLIENTE) {
        std::uint16_t *ptr = (std::uint16_t *) &buffer.at(1);
        return ntohs(*ptr);
    }
    return CANT_BYTES_RESTANTES_JOIN;
}

void ProtocoloServidor::realizar_accion(std::vector<char> &buffer) {
    if (buffer[0] == INICIAR_PARTIDA) {
        std::uint32_t codigo =
                juego.iniciar_partida(cola_cliente);
        enviar_codigo_partida(codigo);
    } else if (buffer[0] == UNIR_PARTIDA) {
        std::vector<char> buffer_host(sizeof(buffer));
        convertir_endianness_join(buffer, buffer_host);
        std::uint32_t *ptr = (std::uint32_t *) &buffer_host.at(1);
        std::uint32_t codigo_cliente = *ptr;
        bool exito = juego.unir_a_partida(cola_cliente, codigo_cliente);
        if (exito) {
            enviar_mensaje_confirmacion(EXITO);
        } else {
            enviar_mensaje_confirmacion(FRACASO);
        }
    } else if (buffer[0] == ENVIO_CLIENTE) {
        juego.enviar_mensaje(obtener_mensaje_enviar(buffer));
    }
}

void ProtocoloServidor::
crear_mensaje_broadcast(std::vector<char> &buffer, std::string &mensaje) {
    std::uint16_t bytes_escenario = mensaje.size();
    std::uint16_t bytes_totales =
            SIZE_BUFF_INICIAL + bytes_escenario;

    buffer.resize(bytes_totales);
    buffer[0] = RESPUESTA_SERVIDOR;
    uint16_t *ptr;

    ptr = (uint16_t *) &buffer.at(1);
    *ptr = htons(bytes_escenario);

    std::memcpy(&buffer[3], mensaje.c_str(), mensaje.size());
}

std::string ProtocoloServidor::
obtener_mensaje_enviar(std::vector<char> &buffer) {
    std::string broadcast(buffer.begin() + 3, buffer.end());
    return broadcast;
}

bool ProtocoloServidor::sigue_vivo() {
    return sigo_vivo;
}

void ProtocoloServidor::cerrar_todo() {
    sigo_vivo = false;
    skt.shutdown(2);
    skt.close();
}

ProtocoloServidor::~ProtocoloServidor() {}
