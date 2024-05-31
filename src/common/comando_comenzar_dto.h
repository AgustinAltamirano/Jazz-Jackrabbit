#ifndef COMANDO_COMENZAR_H
#define COMANDO_COMENZAR_H

#include <stdint.h>

#include "comando_dto.h"

class ComandoComenzarDTO: public ComandoDTO {
private:
    bool empezo;

public:
    ComandoComenzarDTO();

    explicit ComandoComenzarDTO(bool unio);

    bool obtener_empezo();
};

#endif
