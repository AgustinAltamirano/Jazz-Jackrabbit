#include "comando_dto.h"

#include <iostream>

ComandoDTO::ComandoDTO() {
    id_cliente = -1;
    tipo_comando = EN_IDLE;
}

ComandoDTO::ComandoDTO(TipoComando tipo_comando): tipo_comando(tipo_comando) { id_cliente = -1; }

ComandoDTO::ComandoDTO(int32_t& id_cliente, TipoComando comando):
        id_cliente(id_cliente), tipo_comando(comando) {}

TipoComando ComandoDTO::obtener_comando() { return tipo_comando; }
