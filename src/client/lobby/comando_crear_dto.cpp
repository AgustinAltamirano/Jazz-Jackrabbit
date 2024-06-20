#include "comando_crear_dto.h"

ComandoCrearDTO::ComandoCrearDTO(int32_t& id_cliente, std::string nombre_escenario,
                                 TipoPersonaje personaje, int8_t capacidad_partida):
        ComandoDTO(id_cliente, CREAR),
        nombre_escenario(nombre_escenario),
        personaje(personaje),
        capacidad_partida(capacidad_partida),
        codigo_partida() {}

ComandoCrearDTO::ComandoCrearDTO(int32_t codigo_partida):
        ComandoDTO(CREAR), codigo_partida(codigo_partida) {}

ComandoCrearDTO::ComandoCrearDTO(std::string nombre_escenario, TipoPersonaje personaje,
                                 int8_t capacidad_partida):
        ComandoDTO(CREAR),
        nombre_escenario(nombre_escenario),
        personaje(personaje),
        capacidad_partida(capacidad_partida),
        codigo_partida() {}

std::string ComandoCrearDTO::obtener_nombre_escenario() { return nombre_escenario; }

TipoPersonaje ComandoCrearDTO::obtener_personaje() { return personaje; }

int32_t ComandoCrearDTO::obtener_codigo_partida() { return codigo_partida; }

int8_t ComandoCrearDTO::obtener_capacidad_partida() { return capacidad_partida; }
