#include <memory>

#include "common/snapshot_dto.h"
#include "common/socket_dummy.h"

std::shared_ptr<SnapshotDTO> crear_snapshot_test() {
    std::shared_ptr<SnapshotDTO> snapshot = std::make_shared<SnapshotDTO>();
    snapshot->establecer_tipo_escenario(ESCENARIO_CASTLE);
    snapshot->agregar_tiempo_restante(5);
    snapshot->establecer_fin_juego(false);
    snapshot->establecer_hubo_disparo(true);
    snapshot->establecer_hubo_herido(false);
    snapshot->establecer_hubo_muerte(true);

    BloqueEscenarioDTO bloque_escenario(32, 32, 5, 5, 0, PARED);
    snapshot->agregar_bloque_escenario(bloque_escenario);

    ClienteDTO cliente(1, JAZZ, 64, 64, false, CORRER, 10, 100, INFINITA, 0);
    snapshot->agregar_cliente(cliente);

    BalaDTO bala(10, 10, ARMA1, false);
    snapshot->agregar_bala(bala);

    EnemigoDTO enemigo(1, 15, 15, 5, 10, MURCIELAGO, false);
    snapshot->agregar_enemigo(enemigo);

    RecogibleDTO recogible(30, 30, 1, 1, MONEDA_AGARRABLE);
    snapshot->agregar_recogible(recogible);

    return snapshot;
}

void enviar_snapshot_test(SocketDummy* socket, std::shared_ptr<SnapshotDTO>& snapshot_dto,
                     bool* cerrado) {
    std::vector<ClienteDTO>& clientes_dto = snapshot_dto->obtener_clientes();
    std::vector<BloqueEscenarioDTO>& bloques_dto = snapshot_dto->obtener_bloques_escenario();
    std::vector<BalaDTO>& balas_dto = snapshot_dto->obtener_balas();
    std::vector<EnemigoDTO>& enemigos_dto = snapshot_dto->obtener_enemigos();
    std::vector<RecogibleDTO>& recogibles_dto = snapshot_dto->obtener_recogibles();

    const uint32_t num_clientes = htonl(clientes_dto.size());
    const uint32_t num_bloques = htonl(bloques_dto.size());
    const uint32_t num_balas = htonl(balas_dto.size());
    const uint32_t num_enemigos = htonl(enemigos_dto.size());
    const uint32_t num_recogibles = htonl(recogibles_dto.size());

    const auto tipo_escenario = static_cast<uint8_t>(snapshot_dto->obtener_tipo_escenario());
    const int32_t tiempo_restante = htonl(snapshot_dto->obtener_tiempo_restante());
    const auto fin_juego = snapshot_dto->es_fin_juego();
    const auto hubo_disparo = snapshot_dto->obtener_hubo_disparo();
    const auto alguien_fue_herido = snapshot_dto->obtener_hubo_herido();
    const auto alguien_murio = snapshot_dto->obtener_hubo_muerte();

    socket->sendall(&num_clientes, sizeof(num_clientes), cerrado);
    socket->sendall(&num_bloques, sizeof(num_bloques), cerrado);
    socket->sendall(&num_balas, sizeof(num_balas), cerrado);
    socket->sendall(&num_enemigos, sizeof(num_enemigos), cerrado);
    socket->sendall(&num_recogibles, sizeof(num_recogibles), cerrado);
    socket->sendall(&tipo_escenario, sizeof(tipo_escenario), cerrado);
    socket->sendall(&tiempo_restante, sizeof(tiempo_restante), cerrado);
    socket->sendall(&fin_juego, sizeof(fin_juego), cerrado);
    socket->sendall(&hubo_disparo, sizeof(hubo_disparo), cerrado);
    socket->sendall(&alguien_fue_herido, sizeof(alguien_fue_herido), cerrado);
    socket->sendall(&alguien_murio, sizeof(alguien_murio), cerrado);

    for (const auto& cliente_dto: clientes_dto) {
        socket->sendall(&cliente_dto, sizeof(cliente_dto), cerrado);
    }

    for (const auto& bloque_dto: bloques_dto) {
        socket->sendall(&bloque_dto, sizeof(bloque_dto), cerrado);
    }

    for (const auto& bala_dto: balas_dto) {
        socket->sendall(&bala_dto, sizeof(bala_dto), cerrado);
    }

    for (const auto& enemigo_dto: enemigos_dto) {
        socket->sendall(&enemigo_dto, sizeof(enemigo_dto), cerrado);
    }

    for (const auto& recogible_dto: recogibles_dto) {
        socket->sendall(&recogible_dto, sizeof(recogible_dto), cerrado);
    }
}

std::shared_ptr<SnapshotDTO> recibir_snapshot_test(SocketDummy* socket, bool* cerrado) {
    std::shared_ptr<SnapshotDTO> snapshot_dto = std::make_shared<SnapshotDTO>();
    uint32_t cantidad_clientes;
    uint32_t cantidad_bloques;
    uint32_t cantidad_balas;
    uint32_t cantidad_enemigos;
    uint32_t cantidad_recogibles;
    uint8_t tipo_escenario;
    int32_t tiempo_restante;
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

    cantidad_clientes = ntohl(cantidad_clientes);
    cantidad_bloques = ntohl(cantidad_bloques);
    cantidad_balas = ntohl(cantidad_balas);
    cantidad_enemigos = ntohl(cantidad_enemigos);
    cantidad_recogibles = ntohl(cantidad_recogibles);
    tiempo_restante = ntohl(tiempo_restante);

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
