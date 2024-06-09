#include "cliente_deserializador.h"

#include <arpa/inet.h>

ClienteDeserializador::ClienteDeserializador(Socket* socket): socket(socket) {}


SnapshotDTO ClienteDeserializador::deserializar_juego_dto(bool* cerrado) {
    SnapshotDTO snapshot_dto;
    uint8_t cantidad_clientes;
    uint8_t cantidad_bloques;
    char tipo_escenario;
    bool fin_juego;

    int32_t id_cliente;
    char tipo_personaje;
    int32_t pos_x_cliente;
    int32_t pos_y_cliente;
    bool de_espaldas;
    char estado;
    uint32_t vida;
    uint32_t puntos;
    char arma_actual;
    int32_t balas_restantes;

    int32_t pos_x_bloque;
    int32_t pos_y_bloque;
    int32_t angulo_bloque;
    uint32_t ancho_bloque;
    uint32_t alto_bloque;
    char tipo_bloque;

    socket->recvall(&cantidad_clientes, 1, cerrado);
    socket->recvall(&cantidad_bloques, 1, cerrado);
    socket->recvall(&tipo_escenario, 1, cerrado);
    socket->recvall(&fin_juego, sizeof(bool), cerrado);

    for (int i = 0; i < cantidad_clientes; i++) {
        socket->recvall(&id_cliente, sizeof(int32_t), cerrado);
        socket->recvall(&tipo_personaje, 1, cerrado);
        socket->recvall(&pos_x_cliente, sizeof(int32_t), cerrado);
        socket->recvall(&pos_y_cliente, sizeof(int32_t), cerrado);
        socket->recvall(&de_espaldas, sizeof(bool), cerrado);
        socket->recvall(&estado, 1, cerrado);
        socket->recvall(&vida, sizeof(uint32_t), cerrado);
        socket->recvall(&puntos, sizeof(uint32_t), cerrado);
        socket->recvall(&arma_actual, 1, cerrado);
        socket->recvall(&balas_restantes, sizeof(int32_t), cerrado);
        snapshot_dto.agregar_cliente(
                ClienteDTO(ntohl(id_cliente), static_cast<TipoPersonaje>(tipo_personaje),
                           ntohl(pos_x_cliente), ntohl(pos_y_cliente), de_espaldas,
                           static_cast<EstadoPersonaje>(estado), ntohl(vida), ntohl(puntos),
                           static_cast<TipoArma>(arma_actual), ntohl(balas_restantes)));
    }

    for (int i = 0; i < cantidad_bloques; i++) {
        socket->recvall(&pos_x_bloque, sizeof(int32_t), cerrado);
        socket->recvall(&pos_y_bloque, sizeof(int32_t), cerrado);
        socket->recvall(&angulo_bloque, sizeof(int32_t), cerrado);
        socket->recvall(&ancho_bloque, sizeof(uint32_t), cerrado);
        socket->recvall(&alto_bloque, sizeof(uint32_t), cerrado);
        socket->recvall(&tipo_bloque, 1, cerrado);
        snapshot_dto.agregar_bloque_escenario(BloqueEscenarioDTO(
                ntohl(pos_x_bloque), ntohl(pos_y_bloque), ntohl(angulo_bloque), ntohl(ancho_bloque),
                ntohl(alto_bloque), static_cast<TipoBloqueEscenario>(tipo_bloque)));
    }

    snapshot_dto.establecer_fin_juego(fin_juego);
    return snapshot_dto;
}
