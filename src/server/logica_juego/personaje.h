#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <cstdint>
#include <string>
#include <vector>

#include "../../common/snapshot_dto.h"

// los siguientes enum deberian estar en snapshot
typedef enum { JAZZ = 0, SPAZ, LORI } TipoPersonaje;

typedef enum {
    INFINITA = 0,
    ARMA1,
    ARMA2,
    ARMA3,
} ArmaActual;

typedef enum {
    IDLE = 0,
    CORRER,
    DASH,
    DISPARAR_QUIETO,
    SALTAR_ARRIBA,
    SALTAR_ADELANTE,
    CAER_ABAJO,
    CAER_ADELANTE,
    ESTADO_ATAQUE_ESPECIAL,
    INTOXICADO,
    IMPACTADO,
    MUERTE,
} EstadoPersonaje;

typedef enum {
    SALTAR = 0,
    MOVER_IZQ,
    MOVER_DER,
    ACTIVAR_DASH,
    DISPARAR_ACCION,
    ARMA_ANTERIOR,
    ARMA_SIGUIENTE,
    ATAQUEESPECIAL,
    TRUCO1,
    TRUCO2,
    TRUCO3
} AccionJuego;

class personaje {
private:
    int32_t id;
    TipoPersonaje tipo_de_personaje;
    uint32_t alto;
    uint32_t ancho;

    int32_t pos_x;
    int vel_x;
    int aceleracion_x;

    int32_t pos_y;
    int vel_y;
    int aceleracion_y;  // gravedad

    bool sobre_rampa;

    bool de_espaldas;      // invertido en eje x
    bool en_aire;          // define si la aceleracion vertical y horizontal afecta o no
    bool ataque_especial;  // si está realizando un ataque especial las hitboxes hacen daño a los
                           // enemigos

    EstadoPersonaje estado;  // (enum con el tipo de estado del personaje)
    int tiempo_estado;       // (integer contador de cuanto tiempo lleva un personaje en un estado)

    int vida;
    int puntos;

    ArmaActual arma_actual;
    std::vector<int32_t> inventario_balas;

public:
    personaje(int32_t id, TipoPersonaje tipo, int32_t pos_x_inicial, int32_t pos_y_inicial);

    void cambiar_velocidad(const std::vector<AccionJuego>& teclas);  // chequea estado y decide si
                                                                     // moverse, CAMBIA LA VELOCIDAD
    void cambiar_posicion(uint32_t x,
                          uint32_t y);  // despues de revisar colisiones se efectua el cambio real
    void cambiar_estado(bool cae);
    void pasar_tick();

    // los siguientes dos métodos sirven para el chqueo de colisiones
    // Ayuda a decidir con que pared choca el personaje.
    [[nodiscard]] std::vector<int32_t> get_pos_actual() const;
    [[nodiscard]] std::vector<int32_t> get_pos_a_ir() const;
    [[nodiscard]] uint32_t get_ancho() const;
    [[nodiscard]] uint32_t get_alto() const;

    // bool disparar();
    // bool cambiar_arma();
    // bool efectuar_dano();
    // bool respawnear();
};


#endif  // PERSONAJE_H
