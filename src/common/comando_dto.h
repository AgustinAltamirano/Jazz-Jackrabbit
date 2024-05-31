#ifndef COMANDO_DTO_H
#define COMANDO_DTO_H

#include <cstdint>
#include <vector>

#include "tipo_comando.h"

class ComandoDTO {
private:
    TipoComando tipo_comando;
    int32_t id_cliente;

public:
    ComandoDTO();

    explicit ComandoDTO(TipoComando comando);

    ComandoDTO(int32_t& id_cliente, TipoComando comando);

    TipoComando obtener_comando();

    virtual ~ComandoDTO() {}
};

#endif
