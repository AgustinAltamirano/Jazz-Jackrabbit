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
    TRUCO1,
    TRUCO2,
    TRUCO3,
} AccionJuego;

class AccionJuegoDTO {
public:
    uint32_t id_jugador;
    AccionJuego accion;
    explicit AccionJuegoDTO(uint32_t id_jugador, const AccionJuego accion):
            id_jugador(id_jugador), accion(accion) {}
};

#endif  // ACCION_JUEGO_DTO_H
