#include <vector>

#include <netinet/in.h>

#include "../acutest.h"
#include "client/lobby/lobby_protocolo.h"
#include "common/socket_dummy.h"

void test_enviar_comando_crear_partida(void) {
    SocketDummy socket;
    LobbyProtocolo protocolo(&socket);
    bool cerrado = false;

    std::string nombre_escenario_enviado = "Escenario1";
    TipoPersonaje tipo_personaje_enviado = JAZZ;
    int8_t capacidad_partida_enviado = 2;

    ComandoCrearDTO* comando = new ComandoCrearDTO(nombre_escenario_enviado, tipo_personaje_enviado,
                                                   capacidad_partida_enviado);

    protocolo.enviar_comando(comando, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);
    uint8_t len_nombre_escenario_recibido;
    socket.recvall(&len_nombre_escenario_recibido, 1, &cerrado);
    std::vector<char> buffer_recibido(len_nombre_escenario_recibido);
    socket.recvall(buffer_recibido.data(), len_nombre_escenario_recibido, &cerrado);
    TipoPersonaje personaje_recibido;
    socket.recvall(&personaje_recibido, 1, &cerrado);
    int8_t capacidad_partida_recibido;
    socket.recvall(&capacidad_partida_recibido, 1, &cerrado);

    TEST_CHECK(tipo_comando_recibido == CREAR);
    TEST_CHECK(buffer_recibido.data() == nombre_escenario_enviado);
    TEST_CHECK(personaje_recibido == tipo_personaje_enviado);
    TEST_CHECK(capacidad_partida_recibido == capacidad_partida_enviado);
}

void test_enviar_comando_unir_partida(void) {
    SocketDummy socket;
    LobbyProtocolo protocolo(&socket);
    bool cerrado = false;

    int32_t codigo_partida_enviado = 1;
    TipoPersonaje tipo_personaje_enviado = JAZZ;

    ComandoUnirDTO* comando = new ComandoUnirDTO(codigo_partida_enviado, tipo_personaje_enviado);

    protocolo.enviar_comando(comando, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);
    TipoPersonaje personaje_recibido;
    socket.recvall(&personaje_recibido, 1, &cerrado);
    int32_t codigo_partida_recibido;
    socket.recvall(&codigo_partida_recibido, sizeof(int32_t), &cerrado);
    codigo_partida_recibido = ntohl(codigo_partida_recibido);

    TEST_CHECK(tipo_comando_recibido == UNIR);
    TEST_CHECK(personaje_recibido == tipo_personaje_enviado);
    TEST_CHECK(codigo_partida_recibido == codigo_partida_enviado);
}

void test_enviar_comando_validar_escenario(void) {
    SocketDummy socket;
    LobbyProtocolo protocolo(&socket);
    bool cerrado = false;

    std::string nombre_escenario_enviado = "Escenario1";

    ComandoValidarDTO* comando = new ComandoValidarDTO(nombre_escenario_enviado);

    protocolo.enviar_comando(comando, &cerrado);

    char tipo_comando_recibido;
    socket.recvall(&tipo_comando_recibido, 1, &cerrado);
    uint8_t len_nombre_escenario_recibido;
    socket.recvall(&len_nombre_escenario_recibido, 1, &cerrado);
    std::vector<char> buffer_recibido(len_nombre_escenario_recibido);
    socket.recvall(buffer_recibido.data(), len_nombre_escenario_recibido, &cerrado);

    TEST_CHECK(tipo_comando_recibido == VALIDAR_ESCENARIO);
    TEST_CHECK(buffer_recibido.data() == nombre_escenario_enviado);
}

TEST_LIST = {{"Test protocolo crear partida", test_enviar_comando_crear_partida},
             {"Test protocolo unir partida", test_enviar_comando_unir_partida},
             {"Test protocolo validar escenario", test_enviar_comando_validar_escenario},
             {NULL, NULL}};
