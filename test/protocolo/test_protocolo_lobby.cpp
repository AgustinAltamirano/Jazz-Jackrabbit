#include "../acutest.h"
#include <vector>

#include "client/lobby/lobby_serializador.h"
#include "common/tipo_comando.h"

void test_serializar_crear_partida(void) {
    LobbySerializador lobby_serializador;
    std::vector<char> buffer = lobby_serializador.serializar_crear_partida(2);
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == CREAR);
    TEST_CHECK(buffer.at(1) == 2);
}

void test_serializar_unir_partida(void) {
    LobbySerializador lobby_serializador;
    int32_t codigo_partida = 5;
    std::vector<char> buffer = lobby_serializador.serializar_unir_partida(codigo_partida);
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == UNIR);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 5);
}

void test_serializar_comenzar_jugar(void) {
    LobbySerializador lobby_serializador;
    std::vector<char> buffer = lobby_serializador.serializar_comenzar_jugar();
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == COMENZAR);
}

TEST_LIST = {
        {"Test serializar crear partida", test_serializar_crear_partida},
        {"Test serializar unir partida",   test_serializar_unir_partida},
        {"Test serializar comenzar jugar",    test_serializar_comenzar_jugar},
        {NULL, NULL}};
