#include "cliente_recibidor.h"

#include <iostream>

#include <netinet/in.h>

#include "../../common/liberror.h"

ClienteRecibidor::ClienteRecibidor(Socket* skt_cliente, std::atomic<bool>& hablando,
                                   Queue<std::shared_ptr<SnapshotDTO>>* cola_recibidor):
        cliente_deserializador(skt_cliente),
        skt_cliente(skt_cliente),
        hablando(hablando),
        cola_recibidor(cola_recibidor) {}

void ClienteRecibidor::run() {
    try {
        while (hablando) {
            std::shared_ptr<SnapshotDTO> snapshot_dto = std::make_shared<SnapshotDTO>();
            uint8_t cantidad_clientes;
            uint8_t cantidad_bloques;
            uint8_t tipo_escenario;
            bool fin_juego;
            
            bool cerrado;

            skt_cliente->recvall(&cantidad_clientes, sizeof(cantidad_clientes), &cerrado);
            skt_cliente->recvall(&cantidad_bloques, sizeof(cantidad_bloques), &cerrado);
            skt_cliente->recvall(&tipo_escenario, sizeof(tipo_escenario), &cerrado);
            skt_cliente->recvall(&fin_juego, sizeof(fin_juego), &cerrado);

            snapshot_dto->establecer_tipo_escenario(static_cast<TipoEscenario>(tipo_escenario));
            snapshot_dto->establecer_fin_juego(static_cast<bool>(fin_juego));

            for (int i = 0; i < cantidad_clientes; i++) {
                ClienteDTO cliente;
                skt_cliente->recvall(&cliente, sizeof(ClienteDTO), &cerrado);
                snapshot_dto->agregar_cliente(cliente);
            }

            for (int i = 0; i < cantidad_bloques; i++) {
                BloqueEscenarioDTO bloque;
                skt_cliente->recvall(&bloque, sizeof(BloqueEscenarioDTO), &cerrado);
                snapshot_dto->agregar_bloque_escenario(bloque);
            }

            cola_recibidor->push(snapshot_dto);
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    } catch (const LibError& e) {
        std::cerr << "Se cerro la conexion" << std::endl;
    }
}

void ClienteRecibidor::stop() { hablando = false; }
