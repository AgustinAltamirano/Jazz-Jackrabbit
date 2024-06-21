#include <string>
#include <vector>

#include <netinet/in.h>

#include "../acutest.h"
#include "common/snapshot_dto.h"
#include "common/socket_dummy.h"
#include "common/tipo_comando.h"
#include "server/comando_server.h"
#include "server/servidor_protocolo.h"

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
    std::unique_ptr<ComandoServer> comando = protocolo.obtener_comando(&cerrado, id_cliente);

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


TEST_LIST = {{"Test protocolo obtener comando", test_obtener_comando},
             {"Test protocolo enviar id cliente", test_enviar_id_cliente},
             {NULL, NULL}};