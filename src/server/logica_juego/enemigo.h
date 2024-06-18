#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <algorithm>
#include <cstdint>
#include <vector>

#include "../../common/snapshot_dto.h"
#include "../../common/tipo_enemigo.h"
#include "assets/bloqueEscenario.h"

typedef enum {
    ACTIVO = 0,
    MUERTO,
} EstadoEnemigo;

inline bool colision_horizontal(const int32_t jug_x, const int32_t jug_ancho,
                                const bloqueEscenario& bloque) {
    return ((jug_x + jug_ancho > bloque.pos_x && jug_x < bloque.pos_x) ||
            (jug_x < bloque.pos_x + bloque.ancho &&
             jug_x + jug_ancho > bloque.pos_x + bloque.ancho));
}

class enemigo {
public:
    virtual ~enemigo() = default;

    void virtual chequear_colisiones(std::vector<bloqueEscenario>& bloques,
                                     std::vector<bloqueEscenario>& angulos) = 0;
    [[nodiscard]] virtual EstadoEnemigo get_estado() const = 0;
    [[nodiscard]] virtual int32_t get_puntos() const = 0;
    [[nodiscard]] virtual bool esta_invertido() const = 0;
    virtual void mover() = 0;
    virtual void chocar_pared() = 0;
    [[nodiscard]] virtual int32_t atacar() const = 0;
    virtual bool hacer_dano(int32_t puntos_dano) = 0;
    virtual void revivir() = 0;

    virtual int32_t get_pos_x() = 0;
    virtual int32_t get_pos_y() = 0;
    virtual int32_t get_ancho() = 0;
    virtual int32_t get_alto() = 0;

    [[nodiscard]] virtual EnemigoDTO crear_dto() const = 0;
};

#endif  // ENEMIGO_H
