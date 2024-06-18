#include "cliente_recibidor.h"

#include <iostream>

#include <netinet/in.h>

#include "../../common/liberror.h"

ClienteRecibidor::ClienteRecibidor(Socket* skt_cliente, std::atomic<bool>& hablando,
                                   Queue<std::shared_ptr<SnapshotDTO>>* cola_recibidor):
        cliente_protocolo(skt_cliente),
        skt_cliente(skt_cliente),
        hablando(hablando),
        cola_recibidor(cola_recibidor) {}

void ClienteRecibidor::run() {
    bool cerrado;
    try {
        while (hablando) {
            cola_recibidor->push(cliente_protocolo.recibir_snapshot_dto(&cerrado));
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    } catch (const LibError& e) {
        std::cerr << "Se cerro la conexion" << std::endl;
    }
}

void ClienteRecibidor::stop() { hablando = false; }
