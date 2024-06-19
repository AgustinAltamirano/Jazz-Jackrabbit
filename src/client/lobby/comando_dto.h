#ifndef COMANDO_DTO_H
#define COMANDO_DTO_H

#include <cstdint>
#include <vector>

#include "../../common/tipo_comando.h"

class ComandoDTO {
private:
    TipoComando comando;
    int32_t id_cliente;

public:
    ComandoDTO();

    explicit ComandoDTO(TipoComando comando);

    ComandoDTO(int32_t& id_cliente, TipoComando comando);

    TipoComando obtener_comando();

    int32_t obtener_id_cliente();

    virtual ~ComandoDTO() {}
};

#endif
