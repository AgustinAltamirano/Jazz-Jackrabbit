#include "cliente_protocolo.h"

ClienteProtocolo::ClienteProtocolo(SocketAbstracto* socket): socket(socket) {}

std::vector<char> ClienteProtocolo::serializar_comando(const TipoComando& comando) {
    std::vector<char> buffer;
    buffer.push_back(comando);
    return buffer;
}

void ClienteProtocolo::enviar_comando(TipoComando comando, bool* cerrado) {
    std::vector<char> comando_serializado = serializar_comando(comando);
    socket->sendall(comando_serializado.data(), comando_serializado.size(), cerrado);
}

std::shared_ptr<SnapshotDTO> ClienteProtocolo::recibir_snapshot_dto(bool* cerrado) {
    std::shared_ptr<SnapshotDTO> snapshot_dto = std::make_shared<SnapshotDTO>();
    uint8_t cantidad_clientes;
    uint8_t cantidad_bloques;
    uint8_t cantidad_balas;
    uint8_t cantidad_enemigos;
    uint8_t cantidad_recogibles;
    uint8_t tipo_escenario;
    uint8_t tiempo_restante;
    bool fin_juego;
    bool hubo_disparo;
    bool alguien_fue_herido;
    bool alguien_murio;

    socket->recvall(&cantidad_clientes, sizeof(cantidad_clientes), cerrado);
    socket->recvall(&cantidad_bloques, sizeof(cantidad_bloques), cerrado);
    socket->recvall(&cantidad_balas, sizeof(cantidad_balas), cerrado);
    socket->recvall(&cantidad_enemigos, sizeof(cantidad_enemigos), cerrado);
    socket->recvall(&cantidad_recogibles, sizeof(cantidad_recogibles), cerrado);
    socket->recvall(&tipo_escenario, sizeof(tipo_escenario), cerrado);
    socket->recvall(&tiempo_restante, sizeof(tiempo_restante), cerrado);
    socket->recvall(&fin_juego, sizeof(fin_juego), cerrado);
    socket->recvall(&hubo_disparo, sizeof(hubo_disparo), cerrado);
    socket->recvall(&alguien_fue_herido, sizeof(alguien_fue_herido), cerrado);
    socket->recvall(&alguien_murio, sizeof(alguien_murio), cerrado);

    snapshot_dto->establecer_tipo_escenario(static_cast<TipoEscenario>(tipo_escenario));
    snapshot_dto->agregar_tiempo_restante(tiempo_restante);
    snapshot_dto->establecer_fin_juego((fin_juego));
    snapshot_dto->establecer_hubo_disparo(hubo_disparo);
    snapshot_dto->establecer_hubo_herido(alguien_fue_herido);
    snapshot_dto->establecer_hubo_muerte(alguien_murio);

    for (int i = 0; i < cantidad_clientes; i++) {
        ClienteDTO cliente;
        socket->recvall(&cliente, sizeof(ClienteDTO), cerrado);
        snapshot_dto->agregar_cliente(cliente);
    }

    for (int i = 0; i < cantidad_bloques; i++) {
        BloqueEscenarioDTO bloque;
        socket->recvall(&bloque, sizeof(BloqueEscenarioDTO), cerrado);
        snapshot_dto->agregar_bloque_escenario(bloque);
    }

    for (int i = 0; i < cantidad_balas; i++) {
        BalaDTO bala;
        socket->recvall(&bala, sizeof(BalaDTO), cerrado);
        snapshot_dto->agregar_bala(bala);
    }

    for (int i = 0; i < cantidad_enemigos; i++) {
        EnemigoDTO enemigo;
        socket->recvall(&enemigo, sizeof(EnemigoDTO), cerrado);
        snapshot_dto->agregar_enemigo(enemigo);
    }

    for (int i = 0; i < cantidad_recogibles; i++) {
        RecogibleDTO recogible;
        socket->recvall(&recogible, sizeof(RecogibleDTO), cerrado);
        snapshot_dto->agregar_recogible(recogible);
    }

    return snapshot_dto;
}
