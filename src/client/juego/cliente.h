#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <optional>
#include <string>
#include <vector>
#include <memory>

#include "../../common/snapshot_dto.h"

#include "cliente_enviador.h"
#include "cliente_recibidor.h"
#include "cliente_serializador.h"

class Cliente {
private:
    Socket skt_cliente;

    std::atomic<bool> hablando;

    ClienteEnviador cliente_enviador;

    ClienteRecibidor cliente_recibidor;

    ClienteSerializador client_serializador;

    Queue<std::vector<char>> cola_enviador;

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