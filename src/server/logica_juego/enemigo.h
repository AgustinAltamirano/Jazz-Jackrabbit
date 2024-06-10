#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <cstdint>
#include <vector>

typedef enum {
    LAGARTO = 0,
    ESQUELETO,
    MURCIELAGO,
} TipoEnemigo;

typedef enum {
    ACTIVO = 0,
    MUERTO,
} EstadoEnemigo;

class enemigo {
private:
    int32_t id;
    int32_t pos_x;
    int32_t pos_y;
    int32_t vel_x;
    uint32_t ancho;
    uint32_t alto;
    TipoEnemigo tipo;
    EstadoEnemigo estado;
    int contador_estado_muerto;  // cuenta cuantos frames lleva en estado muerto
    bool de_espaldas;
    int32_t vida;
    int32_t puntos;
    int32_t dano;

public:
    enemigo(int32_t id, int32_t pos_x_in, int32_t pos_y_in, TipoEnemigo tipo);
    [[nodiscard]] int32_t get_prox_pos_x() const;
    [[nodiscard]] int32_t get_pos_y() const;
    [[nodiscard]] uint32_t get_alto() const;
    [[nodiscard]] uint32_t get_ancho() const;
    [[nodiscard]] EstadoEnemigo get_estado() const;
    [[nodiscard]] int32_t get_puntos() const;
    [[nodiscard]] bool esta_invertido() const;
    void mover();
    void chocar_pared();
    [[nodiscard]] int32_t atacar() const;
    bool hacer_dano(uint32_t puntos_dano);
    void revivir();

    // virtual EnemigoDTO crear_dto() const = 0;
};

#endif  // ENEMIGO_H
