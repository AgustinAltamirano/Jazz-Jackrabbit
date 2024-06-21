#include "../acutest.h"
#include "test_utils.cpp"
#include "client/juego/cliente_protocolo.h"
#include "common/socket_dummy.h"
#include "common/tipo_comando.h"

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

    std::shared_ptr<SnapshotDTO> snapshot_enviado = crear_snapshot_test();
    enviar_snapshot_test(&socket, snapshot_enviado, &cerrado);

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
