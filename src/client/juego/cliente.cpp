#include "cliente.h"

#include <memory>
#include <sstream>
#include <utility>

#include <sys/socket.h>

Cliente::Cliente(Socket&& socket):
        skt_cliente(std::move(socket)),
        cola_enviador(1000000),
        cola_recibidor(1000000),
        hablando(true),
        cliente_enviador(&skt_cliente, std::ref(hablando), &cola_enviador),
        cliente_recibidor(&skt_cliente, std::ref(hablando), &cola_recibidor),
        cliente_protocolo(&skt_cliente) {
    cliente_enviador.start();
    cliente_recibidor.start();
}

bool Cliente::realizar_accion(const TipoComando& comando) {
    return cola_enviador.try_push(comando);
}

bool Cliente::obtener_snapshot(std::shared_ptr<SnapshotDTO>& snapshot) {
    return cola_recibidor.try_pop(snapshot);
}

void Cliente::join() {
    skt_cliente.shutdown(SHUT_RDWR);
    skt_cliente.close();
    cola_enviador.close();
    cliente_enviador.join();
    cola_recibidor.close();
    cliente_recibidor.join();
}
