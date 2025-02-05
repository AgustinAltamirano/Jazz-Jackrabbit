#ifndef COMANDO_VALIDAR_DTO_H
#define COMANDO_VALIDAR_DTO_H

#include <string>

#include "comando_dto.h"

class ComandoValidarDTO: public ComandoDTO {
private:
    std::string nombre_escenario;

    bool es_valida;

public:
    ComandoValidarDTO(int32_t& id_cliente, std::string nombre_escenario);

    explicit ComandoValidarDTO(bool es_valida);

    explicit ComandoValidarDTO(std::string nombre_escenario);

    ~ComandoValidarDTO() override = default;

    int32_t obtener_info() override;

    std::vector<char> serializar() override;
};

#endif
