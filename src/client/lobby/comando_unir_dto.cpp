#include "comando_unir_dto.h"

ComandoUnirDTO::ComandoUnirDTO(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje):
        ComandoDTO(id_cliente, UNIR), codigo_partida(codigo_partida), personaje(personaje) {}

ComandoUnirDTO::ComandoUnirDTO(bool unio): ComandoDTO(UNIR), unio(unio), codigo_partida() {}

TipoPersonaje ComandoUnirDTO::obtener_personaje() { return personaje; }

int32_t ComandoUnirDTO::obtener_codigo_partida() { return codigo_partida; }

bool ComandoUnirDTO::obtener_unio() { return unio; }
