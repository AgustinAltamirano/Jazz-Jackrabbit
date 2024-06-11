#include <vector>

#include "../acutest.h"
#include "client/lobby/lobby_serializador.h"
#include "common/tipo_comando.h"

void test_serializar_crear_partida(void) {
    LobbySerializador lobby_serializador;
    std::string nombre_escenario = "Escenario1";
    std::vector<char> buffer =
            lobby_serializador.serializar_crear_partida(nombre_escenario, JAZZ, 2);
    TEST_CHECK(buffer.size() == 14);
    TEST_CHECK(buffer.at(0) == CREAR);
    TEST_CHECK(buffer.at(1) == 0x10);
    TEST_CHECK(buffer.at(2) == 'E');
    TEST_CHECK(buffer.at(3) == 's');
    TEST_CHECK(buffer.at(4) == 'c');
    TEST_CHECK(buffer.at(5) == 'e');
    TEST_CHECK(buffer.at(6) == 'n');
    TEST_CHECK(buffer.at(7) == 'a');
    TEST_CHECK(buffer.at(8) == 'r');
    TEST_CHECK(buffer.at(9) == 'i');
    TEST_CHECK(buffer.at(10) == 'o');
    TEST_CHECK(buffer.at(11) == '1');
    TEST_CHECK(buffer.at(12) == JAZZ);
    TEST_CHECK(buffer.at(13) == 2);
}

void test_serializar_unir_partida(void) {
    LobbySerializador lobby_serializador;
    int32_t codigo_partida = 5;
    std::vector<char> buffer = lobby_serializador.serializar_unir_partida(codigo_partida, LORI);
    TEST_CHECK(buffer.size() == 6);
    TEST_CHECK(buffer.at(0) == UNIR);
    TEST_CHECK(buffer.at(0) == LORI);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 5);
}

TEST_LIST = {{"Test serializar crear partida", test_serializar_crear_partida},
             {"Test serializar unir partida", test_serializar_unir_partida},
             {NULL, NULL}};
