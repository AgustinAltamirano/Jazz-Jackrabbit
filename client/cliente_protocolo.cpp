#include <netinet/in.h>
#include <cstring>
#include <string>
#include "cliente_protocolo.h"
#include "../common/liberror.h"

#define SIZE_MSJ_ENTERO 5
#define SIZE_BUFF_INICIAL 3
#define BYTES_CODIGO_PARTIDA 4
#define BYTE_CONFIRMACION 1

ProtocoloCliente::ProtocoloCliente(const std::string &hostname,
                                   const std::string &servname) :
        skt(hostname.c_str(), servname.c_str()) {
    accion["iniciar"] = 0x01;
    accion["unir"] = 0x02;
    accion["enviar"] = 0x03;
}

std::uint32_t ProtocoloCliente::iniciar_partida() {
    std::vector<char> buffer;
    std::string mensaje;
    crear_mensaje_string(mensaje, accion["iniciar"], buffer);
    bool was_closed = false;
    skt.sendall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje del cliente, "
                              "el socket del server se cerro");
    }
    return recibir_numero_partida();
}

std::uint8_t ProtocoloCliente::unir_partida(std::uint32_t partida) {
    std::vector<char> buffer;
    crear_mensaje_entero(partida, buffer);
    bool was_closed = false;
    skt.sendall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje del cliente, "
                              "el socket del server se cerro");
    }
    return recibir_confirmacion_partida();
}

void ProtocoloCliente::enviar_mensaje(std::string &mensaje) {
    std::vector<char> buffer;
    crear_mensaje_string(mensaje, accion["enviar"], buffer);
    bool was_closed = false;
    skt.sendall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje del cliente, "
                              "el socket del server se cerro");
    }
}

std::uint32_t ProtocoloCliente::recibir_numero_partida() {
    std::vector<char> buffer(BYTES_CODIGO_PARTIDA);
    bool was_closed = false;
    skt.recvall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del cliente, "
                              "el socket del server se cerro");
    }
    std::uint32_t *ptr = (std::uint32_t *) &buffer.at(0);
    std::uint32_t numero_partida = ntohl(*ptr);
    return numero_partida;
}

std::uint8_t ProtocoloCliente::recibir_confirmacion_partida() {
    std::vector<char> buffer(BYTE_CONFIRMACION);
    bool was_closed = false;
    skt.recvall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del cliente, "
                              "el socket del server se cerro");
    }
    std::uint8_t confirmacion = buffer[0];
    return confirmacion;
}

void ProtocoloCliente::crear_mensaje_string(
        std::string &mensaje,
        std::uint8_t accion,
        std::vector<char> &buffer) {
    std::uint16_t bytes_escenario = mensaje.size();
    std::uint16_t bytes_totales =
            SIZE_BUFF_INICIAL + bytes_escenario;

    buffer.resize(bytes_totales);
    buffer[0] = accion;
    uint16_t *ptr;

    ptr = (uint16_t *) &buffer.at(1);
    *ptr = htons(bytes_escenario);

    std::memcpy(&buffer[3], mensaje.c_str(), mensaje.size());
}

void ProtocoloCliente::crear_mensaje_entero(
        std::uint32_t partida,
        std::vector<char> &buffer) {
    buffer.resize(SIZE_MSJ_ENTERO);
    buffer[0] = accion["unir"];
    uint32_t *ptr;
    ptr = (uint32_t *) &buffer.at(1);
    *ptr = htonl(partida);
}

std::string ProtocoloCliente::leer_mensaje() {
    std::vector<char> buffer(SIZE_BUFF_INICIAL);
    bool was_closed = false;
    skt.recvall(buffer.data(), buffer.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del cliente, "
                              "el socket del server se cerro");
    }
    std::int16_t bytes_restantes = obtener_bytes_restantes_buffer(buffer);
    buffer.resize(SIZE_BUFF_INICIAL + bytes_restantes);
    skt.recvall(buffer.data() + SIZE_BUFF_INICIAL,
                bytes_restantes, &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del cliente, "
                              "el socket del server se cerro");
    }
    std::string broadcast(buffer.begin() + 3, buffer.end());
    return broadcast;
}

std::int16_t ProtocoloCliente
::obtener_bytes_restantes_buffer(std::vector<char> &buffer) {
    std::uint16_t *ptr = (std::uint16_t *) &buffer.at(1);
    return ntohs(*ptr);
}

void ProtocoloCliente::cerrar_conexion() {
    skt.shutdown(2);
    skt.close();
}
