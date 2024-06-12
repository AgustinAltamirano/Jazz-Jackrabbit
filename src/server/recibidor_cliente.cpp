#include "recibidor_cliente.h"

#include <iostream>
#include <vector>

RecibidorCliente::RecibidorCliente(Socket* socket, std::atomic<bool>& sigo_en_partida,
                                   std::atomic<bool>& sigo_jugando, int32_t& id_cliente,
                                   Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador):
        cola_enviador(cola_enviador),
        id_cliente(id_cliente),
        sigo_en_partida(sigo_en_partida),
        sigo_jugando(sigo_jugando),
        servidor_deserializador(socket) {
    cola_recibidor = nullptr;
}

void RecibidorCliente::run() {
    bool cerrado = false;
    while (sigo_en_partida && !cerrado) {
        try {
            ComandoDTO* nuevo_comando =
                    servidor_deserializador.obtener_comando(&cerrado, id_cliente);
            try {
                cola_recibidor->push(nuevo_comando);
            } catch (const ClosedQueue& e) {
                delete nuevo_comando;
                std::cout << "Juego finalizado" << std::endl;
                break;
            }
        } catch (const std::runtime_error& e) {
            sigo_jugando = false;
            std::cout << "Se desconecto el cliente" << std::endl;
            break;
        }
    }
    sigo_jugando = false;
    sigo_en_partida = false;
    cola_recibidor->close();
}

void RecibidorCliente::establecer_cola_recibidor(Queue<ComandoDTO*>* cola_recibidor) {
    this->cola_recibidor = cola_recibidor;
}

void RecibidorCliente::stop() {
    sigo_jugando = false;
    sigo_en_partida = false;
    cola_recibidor->close();
}
