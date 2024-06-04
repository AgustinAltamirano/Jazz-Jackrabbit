#include "../acutest.h"
#include <vector>

#include "client/juego/cliente_serializador.h"
#include "common/tipo_comando.h"

void test_serializar_comenzar_jugar(void) {
    ClienteSerializador cliente_serializador;
    std::vector<char> buffer = cliente_serializador.serializar_comenzar_jugar();
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == COMENZAR);
}

TEST_LIST = {
        {"Test serializar comenzar jugar", test_serializar_comenzar_jugar},
        {NULL, NULL}};
