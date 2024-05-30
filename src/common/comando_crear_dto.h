#ifndef COMANDO_CREAR_DTO_H
#define COMANDO_CREAR_DTO_H

#include "comando_dto.h"
#include <string>

class ComandoCrearDTO : public ComandoDTO {
private:

    int32_t codigo_partida;

    int8_t capacidad_partida;

public:
    ComandoCrearDTO(int32_t &id_cliente, int8_t capacidad_partida);

    explicit ComandoCrearDTO(int32_t codigo_partida);

    int8_t obtener_capacidad_partida();

    int32_t obtener_codigo_partida();

    virtual ~ComandoCrearDTO() {}
};

#endif
