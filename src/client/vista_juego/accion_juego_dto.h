#ifndef ACCION_JUEGO_DTO_H
#define ACCION_JUEGO_DTO_H

// Esta clase está definida acá provisoriamente, corresponde que esté en common.

typedef enum {
    SALTAR = 0,
    MOVER_IZQ,
    MOVER_DER,
    ACTIVAR_DASH,
    DISPARAR_ACCION,
    ARMA_ANTERIOR,
    ARMA_SIGUIENTE,
} AccionJuego;

class AccionJuegoDTO {
public:
    AccionJuego accion;
    explicit AccionJuegoDTO(const AccionJuego accion): accion(accion) {}
};

#endif  // ACCION_JUEGO_DTO_H
