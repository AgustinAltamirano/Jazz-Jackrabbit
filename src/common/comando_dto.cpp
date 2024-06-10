#include "comando_dto.h"

#include <iostream>

#include "estado_personaje.h"

ComandoDTO::ComandoDTO() {
    id_cliente = -1;
    comando = NINGUNA;
}

ComandoDTO::ComandoDTO(TipoComando comando): comando(comando) { id_cliente = -1; }

ComandoDTO::ComandoDTO(int32_t& id_cliente, TipoComando comando):
        id_cliente(id_cliente), comando(comando) {}

TipoComando ComandoDTO::obtener_comando() { return comando; }

int32_t ComandoDTO::obtener_id_cliente() { return id_cliente; }
