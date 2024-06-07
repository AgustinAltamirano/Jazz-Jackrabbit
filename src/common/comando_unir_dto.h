#ifndef COMANDO_UNIR_DTO_H
#define COMANDO_UNIR_DTO_H

#include <stdint.h>

#include "comando_dto.h"
#include "tipo_personaje.h"

class ComandoUnirDTO: public ComandoDTO {
private:
    int32_t codigo_partida;

    TipoPersonaje personaje;

    bool unio;

public:
    ComandoUnirDTO(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje);

    explicit ComandoUnirDTO(bool unio);

    int32_t obtener_codigo_partida();

    TipoPersonaje obtener_personaje();

    bool obtener_unio();
};

#endif
