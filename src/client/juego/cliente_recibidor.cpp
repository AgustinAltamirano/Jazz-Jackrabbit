#include "cliente_recibidor.h"

#include <iostream>

ClienteRecibidor::ClienteRecibidor(Socket* socket, std::atomic<bool>& hablando,
                                   Queue<std::shared_ptr<SnapshotDTO>>* cola_recibidor):
        cliente_deserializador(socket), hablando(hablando), cola_recibidor(cola_recibidor) {}

void ClienteRecibidor::run() {
    bool cerrado = false;
    try {
        while (!cerrado && hablando) {
            SnapshotDTO snapshot_dto = cliente_deserializador.deserializar_juego_dto(&cerrado);
            cola_recibidor->push(std::shared_ptr<SnapshotDTO>(&snapshot_dto));
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    }
}

void ClienteRecibidor::stop() { hablando = false; }
