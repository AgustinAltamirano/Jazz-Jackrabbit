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

    std::string obtener_nombre_escenario();

    bool obtener_es_valida();

    virtual ~ComandoValidarDTO() {}
};

#endif
