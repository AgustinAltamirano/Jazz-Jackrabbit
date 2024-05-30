#include "aceptador.h"

#include <algorithm>
#include <string>
#include <utility>

#include "comunicador_cliente.h"

Aceptador::Aceptador(Socket* skt_servidor): skt_servidor(skt_servidor) {}

void Aceptador::run() {
    try {
        while (sigo_jugando) {
            Socket skt_aceptado = skt_servidor->accept();
            std::cout << "Nuevo jugador" << std::endl;
            ComunicadorCliente* nuevo_cliente = new ComunicadorCliente(
                    std::move(skt_aceptado), &gestor_partidas, int32_t(clientes.size()));
            clientes.push_back(nuevo_cliente);
            limpiar_clientes();
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
    clientes.remove_if([](ComunicadorCliente* c) {
        if (!c->still_alive()) {
            c->join();
            delete c;
            return true;
        }
        return false;
    });
}

void Aceptador::eliminar_todos_clientes() {
    for (ComunicadorCliente* cliente: clientes) {
        cliente->kill();
        cliente->join();
        delete cliente;
    }
    clientes.clear();
}

void Aceptador::kill() {
    sigo_jugando = false;
    skt_servidor->shutdown(2);
    skt_servidor->close();
}

bool Aceptador::still_alive() { return true; }

Aceptador::~Aceptador() {}
