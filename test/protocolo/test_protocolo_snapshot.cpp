#include "../acutest.h"
#include "client/juego/cliente_protocolo.h"
#include "common/socket_dummy.h"
#include "common/tipo_comando.h"
#include "server/servidor_protocolo.h"

#include "test_utils.cpp"

void test_protocolo_snapshot(void) {
    SocketDummy socket;
    ClienteProtocolo cliente_protocolo(&socket);
    ServidorProtocolo servidor_protocolo(&socket);
    bool cerrado = false;

    std::shared_ptr<SnapshotDTO> snapshot_enviado = crear_snapshot_test();
    servidor_protocolo.enviar_snapshot(snapshot_enviado, &cerrado);
    std::shared_ptr<SnapshotDTO> snapshot_recibido =
            cliente_protocolo.recibir_snapshot_dto(&cerrado);

    TEST_CHECK(snapshot_recibido->obtener_tipo_escenario() ==
               snapshot_enviado->obtener_tipo_escenario());

    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->obtener_pos_x() ==
               snapshot_enviado->obtener_bloques_escenario().data()->obtener_pos_x());
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->obtener_pos_y() ==
               snapshot_enviado->obtener_bloques_escenario().data()->obtener_pos_y());
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->obtener_angulo() ==
               snapshot_enviado->obtener_bloques_escenario().data()->obtener_angulo());
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->obtener_alto() ==
               snapshot_enviado->obtener_bloques_escenario().data()->obtener_alto());
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->obtener_ancho() ==
               snapshot_enviado->obtener_bloques_escenario().data()->obtener_ancho());
    TEST_CHECK(snapshot_recibido->obtener_bloques_escenario().data()->obtener_tipo() ==
               snapshot_enviado->obtener_bloques_escenario().data()->obtener_tipo());

    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_id_cliente() ==
               snapshot_enviado->obtener_clientes().data()->obtener_id_cliente());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_tipo_personaje() ==
               snapshot_enviado->obtener_clientes().data()->obtener_tipo_personaje());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_pos_x() ==
               snapshot_enviado->obtener_clientes().data()->obtener_pos_x());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_pos_y() ==
               snapshot_enviado->obtener_clientes().data()->obtener_pos_y());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_de_espaldas() ==
               snapshot_enviado->obtener_clientes().data()->obtener_de_espaldas());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_estado() ==
               snapshot_enviado->obtener_clientes().data()->obtener_estado());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_vida() ==
               snapshot_enviado->obtener_clientes().data()->obtener_vida());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_puntos() ==
               snapshot_enviado->obtener_clientes().data()->obtener_puntos());
    TEST_CHECK(snapshot_recibido->obtener_clientes().data()->obtener_balas_restantes() ==
               snapshot_enviado->obtener_clientes().data()->obtener_balas_restantes());

    TEST_CHECK(snapshot_recibido->obtener_balas().data()->obtener_pos_x() ==
               snapshot_enviado->obtener_balas().data()->obtener_pos_x());
    TEST_CHECK(snapshot_recibido->obtener_balas().data()->obtener_pos_y() ==
               snapshot_enviado->obtener_balas().data()->obtener_pos_y());
    TEST_CHECK(snapshot_recibido->obtener_balas().data()->obtener_tipo() ==
               snapshot_enviado->obtener_balas().data()->obtener_tipo());
    TEST_CHECK(snapshot_recibido->obtener_balas().data()->obtener_choco() ==
               snapshot_enviado->obtener_balas().data()->obtener_choco());

    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_id() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_id());
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_pos_x() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_pos_x());
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_pos_y() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_pos_y());
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_alto() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_alto());
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_ancho() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_ancho());
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_tipo() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_tipo());
    TEST_CHECK(snapshot_recibido->obtener_enemigos().data()->obtener_invertido() ==
               snapshot_enviado->obtener_enemigos().data()->obtener_invertido());

    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->obtener_pos_x() ==
               snapshot_enviado->obtener_recogibles().data()->obtener_pos_x());
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->obtener_pos_y() ==
               snapshot_enviado->obtener_recogibles().data()->obtener_pos_y());
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->obtener_alto() ==
               snapshot_enviado->obtener_recogibles().data()->obtener_alto());
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->obtener_ancho() ==
               snapshot_enviado->obtener_recogibles().data()->obtener_ancho());
    TEST_CHECK(snapshot_recibido->obtener_recogibles().data()->obtener_tipo() ==
               snapshot_enviado->obtener_recogibles().data()->obtener_tipo());

    TEST_CHECK(snapshot_recibido->obtener_tiempo_restante() ==
               snapshot_enviado->obtener_tiempo_restante());
    TEST_CHECK(snapshot_recibido->es_fin_juego() == snapshot_enviado->es_fin_juego());
    TEST_CHECK(snapshot_recibido->obtener_hubo_disparo() ==
               snapshot_enviado->obtener_hubo_disparo());
    TEST_CHECK(snapshot_recibido->obtener_hubo_herido() == snapshot_enviado->obtener_hubo_herido());
    TEST_CHECK(snapshot_recibido->obtener_hubo_muerte() == snapshot_enviado->obtener_hubo_muerte());
}

TEST_LIST = {{"Test protocolo snapshot", test_protocolo_snapshot}, {NULL, NULL}};
