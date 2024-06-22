#include <string>
#include <vector>

#include <netinet/in.h>

#include "../acutest.h"
#include "common/snapshot_dto.h"
#include "common/socket_dummy.h"
#include "common/tipo_comando.h"
#include "server/comando_server.h"
#include "server/servidor_protocolo.h"

#include "test_utils.cpp"

void test_obtener_comando(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;
    int32_t id_cliente = 1;

    TipoComando comando_enviado = SALTAR;
    std::vector<char> comando_serializado_enviado;
    comando_serializado_enviado.push_back(comando_enviado);

    socket.sendall(comando_serializado_enviado.data(), comando_serializado_enviado.size(),
                   &cerrado);
    std::shared_ptr<ComandoServer> comando = protocolo.obtener_comando(&cerrado, id_cliente);

    TEST_CHECK(comando->obtener_comando() == comando_enviado);
}

void test_enviar_id_cliente(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;
    int32_t id_cliente_enviado = 1;

    protocolo.enviar_id_cliente(id_cliente_enviado, &cerrado);

    int32_t id_cliente_recibido;
    socket.recvall(&id_cliente_recibido, sizeof(int), &cerrado);
    id_cliente_recibido = ntohl(id_cliente_recibido);

    TEST_CHECK(id_cliente_recibido == id_cliente_enviado);
}

void test_enviar_validar_escenario(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;
    bool es_valido_enviado = true;

    protocolo.enviar_validar_escenario(es_valido_enviado, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);

    bool es_valido_recibido;
    socket.recvall(&es_valido_recibido, sizeof(bool), &cerrado);

    TEST_CHECK(VALIDAR_ESCENARIO == tipo_comando_recibido);
    TEST_CHECK(es_valido_recibido == es_valido_enviado);
}

void test_enviar_unir_partida(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;
    bool unio_partida_enviado = false;

    protocolo.enviar_unir_partida(unio_partida_enviado, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);

    bool unio_partida_recibido;
    socket.recvall(&unio_partida_recibido, sizeof(bool), &cerrado);

    TEST_CHECK(UNIR == tipo_comando_recibido);
    TEST_CHECK(unio_partida_recibido == unio_partida_enviado);
}

void test_enviar_crear_partida(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;
    int32_t codigo_partida_enviado = 2;

    protocolo.enviar_crear_partida(codigo_partida_enviado, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);

    int32_t codigo_partida_recibido;
    socket.recvall(&codigo_partida_recibido, 4, &cerrado);
    codigo_partida_recibido = ntohl(codigo_partida_recibido);

    TEST_CHECK(CREAR == tipo_comando_recibido);
    TEST_CHECK(codigo_partida_recibido == codigo_partida_enviado);
}

void test_enviar_error_crear_partida(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;

    protocolo.enviar_error_crear_partida(&cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);

    int32_t codigo_partida_recibido;
    socket.recvall(&codigo_partida_recibido, 4, &cerrado);
    codigo_partida_recibido = ntohl(codigo_partida_recibido);

    TEST_CHECK(CREAR == tipo_comando_recibido);
    TEST_CHECK(codigo_partida_recibido == -1);
}

void test_enviar_snapshot(void) {
    SocketDummy socket;
    ServidorProtocolo protocolo(&socket);
    bool cerrado = false;

    std::shared_ptr<SnapshotDTO> snapshot_enviado = crear_snapshot_test();
    protocolo.enviar_snapshot(snapshot_enviado, &cerrado);

    std::shared_ptr<SnapshotDTO> snapshot_recibido = recibir_snapshot_test(&socket, &cerrado);


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


TEST_LIST = {{"Test protocolo obtener comando", test_obtener_comando},
             {"Test protocolo enviar id cliente", test_enviar_id_cliente},
             {"Test protocolo enviar validar escenario", test_enviar_validar_escenario},
             {"Test protocolo enviar unir partida", test_enviar_unir_partida},
             {"Test protocolo enviar crear partida", test_enviar_crear_partida},
             {"Test protocolo enviar error crear partida", test_enviar_error_crear_partida},
             {"Test protocolo enviar snapshot", test_enviar_snapshot},
             {NULL, NULL}};