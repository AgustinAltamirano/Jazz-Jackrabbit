#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <optional>
#include <string>
#include <vector>

#include "../../common/snapshot_dto.h"

#include "cliente_enviador.h"
#include "cliente_protocolo.h"
#include "cliente_recibidor.h"

class Cliente {
private:
    Socket skt_cliente;

    std::atomic<bool> hablando;

    ClienteEnviador cliente_enviador;

    ClienteRecibidor cliente_recibidor;

    ClienteProtocolo cliente_protocolo;

    Queue<TipoComando> cola_enviador;

    Queue<std::shared_ptr<SnapshotDTO>> cola_recibidor;

public:
    explicit Cliente(Socket&& socket);

    void join();

    bool realizar_accion(const TipoComando& comando);

    bool obtener_snapshot(std::shared_ptr<SnapshotDTO>& snapshot);

    Cliente(const Cliente&) = delete;

    Cliente& operator=(const Cliente&) = delete;
};

#endif  // CLIENTE_H_
