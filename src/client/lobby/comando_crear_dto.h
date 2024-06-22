#ifndef COMANDO_CREAR_DTO_H
#define COMANDO_CREAR_DTO_H

#include <string>

#include "src/common/tipo_personaje.h"

#include "comando_dto.h"

class ComandoCrearDTO: public ComandoDTO {
private:
    std::string nombre_escenario;

    int32_t codigo_partida;

    TipoPersonaje personaje;

    int8_t capacidad_partida;

public:
    ComandoCrearDTO(int32_t& id_cliente, std::string nombre_escenario, TipoPersonaje personaje,
                    int8_t capacidad_partida);

    explicit ComandoCrearDTO(int32_t codigo_partida);

    explicit ComandoCrearDTO(std::string nombre_escenario, TipoPersonaje personaje,
                             int8_t capacidad_partida);

    ~ComandoCrearDTO() override = default;

    int32_t obtener_info() override;

    std::vector<char> serializar() override;
};

#endif
