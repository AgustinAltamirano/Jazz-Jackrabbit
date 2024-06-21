#include <string>
#include <vector>

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


TEST_LIST = {{"Test protocolo enviar comando", test_obtener_comando}, {NULL, NULL}};