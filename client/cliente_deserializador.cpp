#include "cliente_deserializador.h"
#include <iostream>
#include <arpa/inet.h>

ClienteDeserializador::ClienteDeserializador(Socket *socket) : socket(socket) {}


SnapshotDTO ClienteDeserializador::deserializar_juego_dto(bool *cerrado) {
    SnapshotDTO snapshot_dto;
    uint8_t cantidad_clientes;
    int32_t id_cliente;
    bool fin_juego;
    socket->recvall(&cantidad_clientes, 1, cerrado);
    socket->recvall(&fin_juego, sizeof(bool), cerrado);
    for (int i = 0; i < cantidad_clientes; i++) {
        socket->recvall(&id_cliente, sizeof(int32_t), cerrado);
        snapshot_dto.agregar_cliente(ClienteDTO(ntohl(id_cliente)));
    }
    snapshot_dto.establecer_fin_juego(fin_juego);
    return snapshot_dto;
}
