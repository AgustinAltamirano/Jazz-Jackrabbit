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

TEST_LIST = {{"Test enviar comando", test_enviar_comando},
             {NULL, NULL}};
