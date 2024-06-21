#include "../acutest.h"
#include "client/juego/cliente_protocolo.h"
#include "common/socket_dummy.h"
#include "common/tipo_comando.h"

/*******************************FUNCIONES AUXILIARES******************************************/

std::shared_ptr<SnapshotDTO> crear_snapshot() {
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

void enviar_snapshot(SocketDummy* socket, std::shared_ptr<SnapshotDTO>& snapshot_dto,
                     bool* cerrado) {
    std::vector<ClienteDTO>& clientes_dto = snapshot_dto->obtener_clientes();
    std::vector<BloqueEscenarioDTO>& bloques_dto = snapshot_dto->obtener_bloques_escenario();
    std::vector<BalaDTO>& balas_dto = snapshot_dto->obtener_balas();
    std::vector<EnemigoDTO>& enemigos_dto = snapshot_dto->obtener_enemigos();
    std::vector<RecogibleDTO>& recogibles_dto = snapshot_dto->obtener_recogibles();

    uint8_t num_clientes = clientes_dto.size();
    uint8_t num_bloques = bloques_dto.size();
    uint8_t num_balas = balas_dto.size();
    uint8_t num_enemigos = enemigos_dto.size();
    uint8_t num_recogibles = recogibles_dto.size();

    auto tipo_escenario = static_cast<uint8_t>(snapshot_dto->obtener_tipo_escenario());
    auto tiempo_restante = static_cast<uint8_t>(snapshot_dto->obtener_tiempo_restante());
    auto fin_juego = snapshot_dto->es_fin_juego();
    auto hubo_disparo = snapshot_dto->obtener_hubo_disparo();
    auto alguien_fue_herido = snapshot_dto->obtener_hubo_herido();
    auto alguien_murio = snapshot_dto->obtener_hubo_muerte();

    socket->sendall(&num_clientes, sizeof(uint8_t), cerrado);
    socket->sendall(&num_bloques, sizeof(uint8_t), cerrado);
    socket->sendall(&num_balas, sizeof(uint8_t), cerrado);
    socket->sendall(&num_enemigos, sizeof(uint8_t), cerrado);
    socket->sendall(&num_recogibles, sizeof(uint8_t), cerrado);
    socket->sendall(&tipo_escenario, sizeof(uint8_t), cerrado);
    socket->sendall(&tiempo_restante, sizeof(uint8_t), cerrado);
    socket->sendall(&fin_juego, sizeof(bool), cerrado);
    socket->sendall(&hubo_disparo, sizeof(bool), cerrado);
    socket->sendall(&alguien_fue_herido, sizeof(bool), cerrado);
    socket->sendall(&alguien_murio, sizeof(bool), cerrado);

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

/*********************************************************************************************/

void test_enviar_comando(void) {
    SocketDummy socket;
    ClienteProtocolo protocolo(&socket);
    bool cerrado = false;

    TipoComando comando_enviado = SALTAR;
    protocolo.enviar_comando(comando_enviado, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);

    TEST_CHECK(tipo_comando_recibido == comando_enviado);
}

void test_obtener_snapshot(void) {
    SocketDummy socket;
    ClienteProtocolo protocolo(&socket);
    bool cerrado = false;

    std::shared_ptr<SnapshotDTO> snapshot_enviado = crear_snapshot();
    enviar_snapshot(&socket, snapshot_enviado, &cerrado);

    std::shared_ptr<SnapshotDTO> snapshot_recibido = protocolo.recibir_snapshot_dto(&cerrado);

    TEST_CHECK(snapshot_recibido->obtener_tipo_escenario() ==
               snapshot_enviado->obtener_tipo_escenario());

    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->pos_x ==
               snapshot_enviado->obtener_bloques_escenario().data()->pos_x);
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->pos_y ==
               snapshot_enviado->obtener_bloques_escenario().data()->pos_y);
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->angulo ==
               snapshot_enviado->obtener_bloques_escenario().data()->angulo);
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->alto ==
               snapshot_enviado->obtener_bloques_escenario().data()->alto);
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->ancho ==
               snapshot_enviado->obtener_bloques_escenario().data()->ancho);
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->tipo ==
               snapshot_enviado->obtener_bloques_escenario().data()->tipo);

    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->id_cliente ==
               snapshot_enviado->obtener_clientes().data()->id_cliente);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->tipo_personaje ==
               snapshot_enviado->obtener_clientes().data()->tipo_personaje);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->pos_x ==
               snapshot_enviado->obtener_clientes().data()->pos_x);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->pos_y ==
               snapshot_enviado->obtener_clientes().data()->pos_y);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->de_espaldas ==
               snapshot_enviado->obtener_clientes().data()->de_espaldas);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->estado ==
               snapshot_enviado->obtener_clientes().data()->estado);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->vida ==
               snapshot_enviado->obtener_clientes().data()->vida);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->puntos ==
               snapshot_enviado->obtener_clientes().data()->puntos);
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->balas_restantes ==
               snapshot_enviado->obtener_clientes().data()->balas_restantes);

    TEST_CHECK(snapshot_recibido->obtener_balas().data()->pos_x ==
               snapshot_enviado->obtener_balas().data()->pos_x);
    TEST_CHECK(snapshot_recibido->obtener_balas().data()->pos_y ==
               snapshot_enviado->obtener_balas().data()->pos_y);
    TEST_CHECK(snapshot_recibido->obtener_balas().data()->tipo ==
               snapshot_enviado->obtener_balas().data()->tipo);
    TEST_CHECK(snapshot_recibido->obtener_balas().data()->choco ==
               snapshot_enviado->obtener_balas().data()->choco);

    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->id ==
               snapshot_enviado->obtener_enemigos().data()->id);
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->pos_x ==
    snapshot_enviado->obtener_enemigos().data()->pos_x);
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->pos_y ==
    snapshot_enviado->obtener_enemigos().data()->pos_y);
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->alto ==
    snapshot_enviado->obtener_enemigos().data()->alto);
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->ancho ==
               snapshot_enviado->obtener_enemigos().data()->ancho);
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->tipo ==
               snapshot_enviado->obtener_enemigos().data()->tipo);
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->invertido ==
               snapshot_enviado->obtener_enemigos().data()->invertido);

    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->pos_x ==
               snapshot_enviado->obtener_recogibles().data()->pos_x);
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->pos_y ==
               snapshot_enviado->obtener_recogibles().data()->pos_y);
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->alto ==
               snapshot_enviado->obtener_recogibles().data()->alto);
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->ancho ==
               snapshot_enviado->obtener_recogibles().data()->ancho);
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->tipo ==
               snapshot_enviado->obtener_recogibles().data()->tipo);

    TEST_CHECK(snapshot_recibido->obtener_tiempo_restante() ==
               snapshot_enviado->obtener_tiempo_restante());
    TEST_CHECK(snapshot_recibido->es_fin_juego() == snapshot_enviado->es_fin_juego());
    TEST_CHECK(snapshot_recibido->obtener_hubo_disparo() ==
               snapshot_enviado->obtener_hubo_disparo());
    TEST_CHECK(snapshot_recibido->obtener_hubo_herido() == snapshot_enviado->obtener_hubo_herido());
    TEST_CHECK(snapshot_recibido->obtener_hubo_muerte() == snapshot_enviado->obtener_hubo_muerte());
}

TEST_LIST = {{"Test enviar comando", test_enviar_comando},
             {"Test obtener snapshot", test_obtener_snapshot},
             {NULL, NULL}};
