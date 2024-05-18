#ifndef CLIENTE_PROTOCOLO_H_
#define CLIENTE_PROTOCOLO_H_

#include <map>
#include <vector>
#include <string>
#include "../common/socket.h"

class ProtocoloCliente {
private:
    Socket skt;
    std::map<std::string, std::uint8_t> accion;

    void crear_mensaje_string(std::string &mensaje,
                              std::uint8_t accion,
                              std::vector<char> &buffer);

    void crear_mensaje_entero(std::uint32_t partida, std::vector<char> &buffer);

    std::int16_t obtener_bytes_restantes_buffer(std::vector<char> &buffer);

    std::uint8_t recibir_confirmacion_partida();

    std::uint32_t recibir_numero_partida();

public:
    ProtocoloCliente(const std::string &hostname, const std::string &servname);

    std::uint32_t iniciar_partida();

    std::uint8_t unir_partida(std::uint32_t partida);

    void enviar_mensaje(std::string &mensaje);

    std::string leer_mensaje();

    void cerrar_conexion();

    ProtocoloCliente(const ProtocoloCliente &) = delete;

    ProtocoloCliente &operator=(const ProtocoloCliente &) = delete;
};

#endif  // CLIENTE_PROTOCOLO_H_
