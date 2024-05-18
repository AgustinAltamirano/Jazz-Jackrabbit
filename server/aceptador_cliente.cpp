#include <algorithm>
#include <utility>
#include <string>
#include "aceptador_cliente.h"
#include "servidor_protocolo.h"
#include "comunicador_cliente.h"

AceptadorCliente::AceptadorCliente(std::string &servname) :
        skt_escuchador(Socket(servname.c_str())) {}

void AceptadorCliente::run() {
    try {
        MonitorPartidas monitor_partidas;
        while (sigo_vivo) {
            Socket acceptado = skt_escuchador.accept();
            manejar_cliente(std::move(acceptado),
                            monitor_partidas);
            limpiar_clientes();
        }
    } catch (const std::exception &err) {
        if (sigo_vivo) {
            std::cerr << "Excepcion capturada: " << err.what() << "\n";
        }
        eliminar_todos_clientes();
        sigo_vivo = false;
    }
}

void AceptadorCliente::manejar_cliente(
        Socket skt_cliente,
        MonitorPartidas &monitor_partidas) {
    Thread *t = new ComunicadorCliente(std::move(skt_cliente),
                            monitor_partidas);
    threads.push_back(t);
    t->start();
}

void AceptadorCliente::limpiar_clientes() {
    auto terminado = [](Thread *thread) {
        if (!thread->sigue_vivo()) {
            thread->kill();
            thread->join();
            delete thread;
            return true;
        }
        return false;
    };
    threads.erase(std::remove_if(threads.begin(),
                                 threads.end(), terminado), threads.end());
}

void AceptadorCliente::eliminar_todos_clientes() {
    for (Thread *cliente: threads) {
        cliente->kill();
        cliente->join();
        delete cliente;
    }
    threads.clear();
}

void AceptadorCliente::kill() {
    sigo_vivo = false;
    skt_escuchador.shutdown(2);
    skt_escuchador.close();
}

bool AceptadorCliente::sigue_vivo() {
    return true;
}
