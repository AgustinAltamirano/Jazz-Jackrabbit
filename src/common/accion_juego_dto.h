#ifndef ACCION_JUEGO_DTO_H
#define ACCION_JUEGO_DTO_H

#include "tipo_comando.h"
class AccionJuegoDTO {
public:
    TipoComando accion;
    explicit AccionJuegoDTO(const TipoComando accion): accion(accion) {}
};

#endif  // ACCION_JUEGO_DTO_H
