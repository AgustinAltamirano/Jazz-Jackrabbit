#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <cstdint>
#include <vector>

#include "../../common/snapshot_dto.h"
#include "../../common/tipo_enemigo.h"

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
    int32_t ancho;
    int32_t alto;
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
    [[nodiscard]] int32_t get_pos_x() const;
    [[nodiscard]] int32_t get_pos_y() const;
    [[nodiscard]] int32_t get_alto() const;
    [[nodiscard]] int32_t get_ancho() const;
    [[nodiscard]] EstadoEnemigo get_estado() const;
    [[nodiscard]] int32_t get_puntos() const;
    [[nodiscard]] bool esta_invertido() const;
    void mover();
    void chocar_pared();
    [[nodiscard]] int32_t atacar() const;
    bool hacer_dano(int32_t puntos_dano);
    void revivir();

    EnemigoDTO crear_dto() const;
};

#endif  // ENEMIGO_H
