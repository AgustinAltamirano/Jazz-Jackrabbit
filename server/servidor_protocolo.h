#ifndef SERVIDOR_PROTOCOLO_H_
#define SERVIDOR_PROTOCOLO_H_

#include <string>
#include <vector>
#include <atomic>
#include "../common/socket.h"
#include "../common/queue.h"
#include "juego.h"

class ProtocoloServidor {
private:
    Socket skt;
    Juego &juego;
    std::atomic<bool> sigo_vivo{true};
    Queue<std::string> &cola_cliente;

    std::int16_t obtener_bytes_restantes(std::vector<char> &buffer);

    void convertir_endianness_join(const std::vector<char> &buffer_viejo,
                                   std::vector<char> &buffer_nuevo);

    void realizar_accion(std::vector<char> &buffer);

    void enviar_codigo_partida(std::uint32_t codigo);

    void enviar_mensaje_confirmacion(std::uint8_t confirmacion);

    void recibir_mensaje_cliente(std::vector<char> &buffer);

    std::string obtener_mensaje_enviar(std::vector<char> &buffer);

    void crear_mensaje_broadcast(std::vector<char> &buffer,
                                 std::string &mensaje);

public:
    ProtocoloServidor(Socket
                      skt_cliente,
                      Juego &juego,
                      Queue<std::string>
                      &cola_cliente);

    void enviar_mensaje();

    void recibir_mensaje();

    bool sigue_vivo();

    void cerrar_todo();

    ~ProtocoloServidor();

    ProtocoloServidor(const ProtocoloServidor &) = delete;

    ProtocoloServidor &operator=(const ProtocoloServidor &) = delete;
};

#endif  // SERVIDOR_PROTOCOLO_H_
