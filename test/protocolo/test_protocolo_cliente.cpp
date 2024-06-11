#include <vector>

#include "../acutest.h"
#include "client/juego/cliente_serializador.h"
#include "common/tipo_comando.h"

void test_serializar_comando(void) {
    ClienteSerializador cliente_serializador;
    std::vector<char> buffer = cliente_serializador.serializar_comando(SALTAR);
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == SALTAR);
}

TEST_LIST = {{"Test serializar saltar", test_serializar_comando}, {NULL, NULL}};
