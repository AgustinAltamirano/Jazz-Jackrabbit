#include "../acutest.h"
#include <vector>
#include <string>

#include "../../src/server/servidor_serializador.h"

#include "../../src/common/snapshot_dto.h"
#include "../../src/common/tipo_comando.h"

void test_serializar_crear_partida(void) {
    ServidorSerializador servidor_serializador;
    int32_t codigo_partida = 3;
    std::vector<char> buffer = servidor_serializador.serializar_crear_partida(codigo_partida);
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == CREAR);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 3);
}

void test_serializar_error_crear_partida(void) {
    ServidorSerializador servidor_serializador;
    std::vector<char> buffer = servidor_serializador.serializar_error_crear_partida();
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == CREAR);
    TEST_CHECK(buffer.at(4) == -1);
}

void test_serializar_unir_partida_true(void) {
    ServidorSerializador servidor_serializador;
    std::vector<char> buffer = servidor_serializador.serializar_unir_partida(true);
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == UNIR);
    TEST_CHECK(buffer.at(1) == 0x01);
}

void test_serializar_unir_partida_false(void) {
    ServidorSerializador servidor_serializador;
    std::vector<char> buffer = servidor_serializador.serializar_unir_partida(false);
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == UNIR);
    TEST_CHECK(buffer.at(1) == 0x00);
}

void test_serializar_comenzar_jugar_true(void) {
    ServidorSerializador servidor_serializador;
    std::vector<char> buffer = servidor_serializador.serializar_iniciar_juego(true);
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == COMENZAR);
    TEST_CHECK(buffer.at(1) == 1);
}

void test_serializar_comenzar_jugar_false(void) {
    ServidorSerializador servidor_serializador;
    std::vector<char> buffer = servidor_serializador.serializar_iniciar_juego(false);
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == COMENZAR);
    TEST_CHECK(buffer.at(1) == 0);
}

void test_serializar_id_cliente(void) {
    ServidorSerializador servidor_serializador;
    int32_t id_cliente = 10;
    std::vector<char> buffer = servidor_serializador.serializar_id_cliente(id_cliente);
    TEST_CHECK(buffer.size() == 4);
    TEST_CHECK(buffer.at(0) == 0x00);
    TEST_CHECK(buffer.at(1) == 0x00);
    TEST_CHECK(buffer.at(2) == 0x00);
    TEST_CHECK(buffer.at(3) == 10);
}

// Soldier position or infected position
void test_serializar_snapshot_dto(void) {
    ServidorSerializador servidor_serializador;
    ClienteDTO cliente_dto(10);
    SnapshotDTO snapshot_dto;
    snapshot_dto.agregar_cliente(cliente_dto);
    snapshot_dto.establecer_fin_juego(true);
    std::vector<char> buffer = servidor_serializador.serializar_snapshot(snapshot_dto);

    TEST_CHECK(buffer.size() == 8);
    TEST_CHECK(buffer.at(0) == 0x01);
    TEST_CHECK(buffer.at(1) == 0x01);
    TEST_CHECK(buffer.at(2) == 0x00);
    TEST_CHECK(buffer.at(3) == 0x00);

    TEST_CHECK(buffer.at(4) == 0x00);
    TEST_CHECK(buffer.at(5) == 0x00);
    TEST_CHECK(buffer.at(6) == 0x00);
    TEST_CHECK(buffer.at(7) == 10);
}


TEST_LIST = {
        {"Test serializar crear partida",       test_serializar_crear_partida},
        {"Test serializar error crear partida", test_serializar_error_crear_partida},
        {"Test serializar unir partida true",   test_serializar_unir_partida_true},
        {"Test serializar unir partida false",  test_serializar_unir_partida_false},
        {"Test serializar comenzar jugar",      test_serializar_comenzar_jugar_true},
        {"Test serializar comenzar false",      test_serializar_comenzar_jugar_false},
        {"Test serializar id cliente ",         test_serializar_id_cliente},
        {"Test serializar snapshot dto ",       test_serializar_snapshot_dto},
        {NULL, NULL}};