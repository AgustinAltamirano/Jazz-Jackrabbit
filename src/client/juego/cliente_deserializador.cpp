#include "cliente_deserializador.h"

#include <arpa/inet.h>

#include "../../common/tipo_bloque_escenario.h"

ClienteDeserializador::ClienteDeserializador(Socket* socket): socket(socket) {}


std::shared_ptr<SnapshotDTO> ClienteDeserializador::deserializar_snapshot_dto() {
    std::shared_ptr<SnapshotDTO> snapshot_dto = std::make_shared<SnapshotDTO>();
    uint8_t cantidad_clientes;
    uint8_t cantidad_bloques;
    uint8_t tipo_escenario;
    bool fin_juego;
    bool cerrado;

    socket->recvall(&cantidad_clientes, sizeof(cantidad_clientes), &cerrado);
    socket->recvall(&cantidad_bloques, sizeof(cantidad_bloques), &cerrado);
    socket->recvall(&tipo_escenario, sizeof(tipo_escenario), &cerrado);
    socket->recvall(&fin_juego, sizeof(fin_juego), &cerrado);

    snapshot_dto->establecer_tipo_escenario(static_cast<TipoEscenario>(tipo_escenario));
    snapshot_dto->establecer_fin_juego(static_cast<bool>(fin_juego));

    for (int i = 0; i < cantidad_clientes; i++) {
        ClienteDTO cliente;
        socket->recvall(&cliente, sizeof(ClienteDTO), &cerrado);
        snapshot_dto->agregar_cliente(cliente);
    }

    for (int i = 0; i < cantidad_bloques; i++) {
        BloqueEscenarioDTO bloque;
        socket->recvall(&bloque, sizeof(BloqueEscenarioDTO), &cerrado);
        snapshot_dto->agregar_bloque_escenario(bloque);
    }
    return snapshot_dto;
}
