#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <optional>
#include <string>
#include <vector>

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

    Queue<SnapshotDTO> cola_recibidor;

public:
    explicit Cliente(Socket&& socket);

    void join();

    void comenzar_jugar();

    std::optional<SnapshotDTO> obtener_snapshot();

    Cliente(const Cliente&) = delete;

    Cliente& operator=(const Cliente&) = delete;
};

#endif  // CLIENTE_H_
