#ifndef COMUNICADOR_CLIENTE_H_
#define COMUNICADOR_CLIENTE_H_

#include <atomic>
#include <vector>
#include <string>
#include "../common/thread.h"
#include "../common/socket.h"
#include "monitor_partidas.h"
#include "servidor_protocolo.h"
#include "recibidor_cliente.h"

class ComunicadorCliente : public Thread {
private:
    std::atomic<bool> sigo_vivo{true};
    Queue<std::string> cola_jugador;
    Juego juego;
    ProtocoloServidor protocolo;

    void enviar_mensaje();

public:
    ComunicadorCliente(Socket skt_jugador,
                       MonitorPartidas &monitor_partidas);

    void run() override;

    bool sigue_vivo() override;

    void kill() override;

    ComunicadorCliente(const ComunicadorCliente &) = delete;

    ComunicadorCliente &operator=(const ComunicadorCliente &) = delete;
};

#endif  // COMUNICADOR_CLIENTE_H_
