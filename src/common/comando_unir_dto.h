#ifndef COMANDO_UNIR_DTO_H
#define COMANDO_UNIR_DTO_H

#include "comando_dto.h"
#include <stdint.h>

class ComandoUnirDTO : public ComandoDTO {
private:
    int32_t codigo_partida;

    bool unio;

public:
    ComandoUnirDTO(int32_t id_cliente, int32_t codigo_partida);

    explicit ComandoUnirDTO(bool unio);

    int32_t obtener_codigo_partida();

    bool obtener_unio();
};

#endif
