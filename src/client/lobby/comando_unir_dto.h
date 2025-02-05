#ifndef COMANDO_UNIR_DTO_H
#define COMANDO_UNIR_DTO_H

#include <cstdint>

#include "../../common/tipo_personaje.h"

#include "comando_dto.h"

class ComandoUnirDTO: public ComandoDTO {
private:
    int32_t codigo_partida;

    TipoPersonaje personaje;

    bool unio;

public:
    ComandoUnirDTO(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje);

    explicit ComandoUnirDTO(bool unio);

    explicit ComandoUnirDTO(int32_t codigo_partida, TipoPersonaje personaje);

    int32_t obtener_info() override;

    std::vector<char> serializar() override;
};

#endif
