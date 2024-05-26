#include <sstream>
#include "cliente.h"

Cliente::Cliente(const std::string &hostname, const std::string &servname) :
        socket(hostname.c_str(), servname.c_str()), cola_enviador(1000000), cola_recibidor(1000000), hablando(true),
        cliente_enviador(&socket, std::ref(hablando), &cola_enviador),
        cliente_recibidor(&socket, std::ref(hablando), &cola_recibidor) {
    cliente_enviador.start();
    cliente_recibidor.start();
    comenzar_jugar();
}

void Cliente::comenzar_jugar() {
    cola_enviador.try_push(client_serializador.serializar_comenzar_jugar());
}

std::optional<SnapshotDTO> Cliente::obtener_snapshot() {
    SnapshotDTO snapshot_dto;
    if (cola_recibidor.try_pop(snapshot_dto)) {
        return std::optional<SnapshotDTO>(snapshot_dto);
    } else {
        return std::optional<SnapshotDTO>();
    }
}

void Cliente::join() {
    socket.shutdown(2);
    socket.close();
    cola_enviador.close();
    cliente_enviador.join();
    cola_recibidor.close();
    cliente_recibidor.join();
}
