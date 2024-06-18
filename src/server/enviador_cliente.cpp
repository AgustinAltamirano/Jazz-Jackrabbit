#include "enviador_cliente.h"

#include <memory>
#include "../common/validador_de_mapas.h"

EnviadorCliente::EnviadorCliente(Socket* skt_cliente, std::atomic<bool>& sigo_en_partida,
                                 int32_t& id_cliente, Queue<std::shared_ptr<SnapshotDTO>>& cola_cliente):
        sigo_en_partida(sigo_en_partida),
        cola_enviador(cola_cliente),
        servidor_protocolo(skt_cliente),
        id_cliente(id_cliente) {
    sigo_en_partida = true;
}

void EnviadorCliente::run() {
    servidor_protocolo.enviar_id_cliente(id_cliente, &cerrado);
    while (sigo_en_partida) {
        try {
            while (!cerrado) {
                std::shared_ptr<SnapshotDTO> snapshot_dto = cola_enviador.pop();
                servidor_protocolo.enviar_snapshot(snapshot_dto, &cerrado);
            }
        } catch (const ClosedQueue& e) {
            std::cout << "Se cerro la cola correctamente" << std::endl;
        }
        sigo_en_partida = false;
    }
}

void EnviadorCliente::cerrar_cola() { cola_enviador.close(); }

void EnviadorCliente::stop() { sigo_en_partida = false; }
