#include "comando_crear_dto.h"

ComandoCrearDTO::ComandoCrearDTO(int32_t &id_cliente, int8_t capacidad_partida) :
        ComandoDTO(id_cliente, CREAR), capacidad_partida(capacidad_partida) {}

ComandoCrearDTO::ComandoCrearDTO(int32_t codigo_partida) : ComandoDTO(CREAR), codigo_partida(codigo_partida) {}

int32_t ComandoCrearDTO::obtener_codigo_partida() { return codigo_partida; }

int8_t ComandoCrearDTO::obtener_capacidad_partida() { return capacidad_partida; }
