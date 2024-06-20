#include "aceptador.h"

#include <algorithm>
#include <utility>

#include <sys/socket.h>

#include "comunicador_cliente.h"

Aceptador::Aceptador(Socket* skt_servidor): skt_servidor(skt_servidor) {}

void Aceptador::run() {
    try {
        while (sigo_jugando) {
            Socket skt_aceptado = skt_servidor->accept();
            clientes.emplace_back(std::move(skt_aceptado), &gestor_partidas, int32_t(clientes.size()));
            limpiar_clientes();
            gestor_partidas.borrar_partidas_finalizadas();
        }
    } catch (const std::exception& err) {
        if (sigo_jugando) {
            std::cerr << "Excepcion capturada: " << err.what() << "\n";
        }
        gestor_partidas.join_partidas();
        eliminar_todos_clientes();
        sigo_jugando = false;
    }
}

void Aceptador::limpiar_clientes() {
    clientes.remove_if([](ComunicadorCliente& cliente) {
        if (!cliente.sigue_en_partida()) {
            cliente.limpiar_cliente();
            return true;
        }
        return false;
    });
}

void Aceptador::eliminar_todos_clientes() {
    for (ComunicadorCliente& cliente: clientes) {
        cliente.matar_cliente();
    }
    clientes.clear();
}

void Aceptador::stop() {
    sigo_jugando = false;
    skt_servidor->shutdown(SHUT_RDWR);
    skt_servidor->close();
    eliminar_todos_clientes();
}

Aceptador::~Aceptador() = default;
