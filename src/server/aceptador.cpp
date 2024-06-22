#include "aceptador.h"

#include <algorithm>
#include <utility>
#include <vector>

#include <sys/socket.h>

#include "src/common/liberror.h"

#include "comunicador_cliente.h"

Aceptador::Aceptador(Socket* skt_servidor): skt_servidor(skt_servidor), proximo_id_cliente(0) {}

void Aceptador::run() {
    try {
        while (sigo_jugando) {
            Socket* skt_aceptado = (Socket*)skt_servidor->accept();
            clientes.emplace(std::piecewise_construct, std::forward_as_tuple(proximo_id_cliente),
                             std::forward_as_tuple(std::move(*skt_aceptado), &gestor_partidas,
                                                   proximo_id_cliente));
            proximo_id_cliente++;
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
    std::vector<int32_t> clientes_a_borrar;
    for (auto& [id, cliente]: clientes) {
        if (!cliente.sigue_en_partida()) {
            cliente.limpiar_cliente();
            clientes_a_borrar.push_back(id);
        }
    }
    for (const auto& id: clientes_a_borrar) {
        clientes.erase(id);
    }
}

void Aceptador::eliminar_todos_clientes() {
    for (auto& [id, cliente]: clientes) {
        cliente.matar_cliente();
    }
}

void Aceptador::stop() {
    sigo_jugando = false;
    skt_servidor->shutdown(SHUT_RDWR);
    skt_servidor->close();
}

Aceptador::~Aceptador() = default;
