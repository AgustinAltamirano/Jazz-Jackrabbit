#ifndef MURCIELAGO_H
#define MURCIELAGO_H

#include <vector>

#include "enemigo.h"

class Murcielago: public enemigo {
private:
    int32_t id;
    int32_t pos_x;
    int32_t pos_y;
    int32_t vel_x;
    int32_t ancho;
    int32_t alto;
    const TipoEnemigo tipo;
    EstadoEnemigo estado;
    int contador_estado_muerto;  // cuenta cuantos frames lleva en estado muerto
    bool de_espaldas;
    int32_t vida;
    int32_t puntos;
    int32_t dano;

public:
    Murcielago(int32_t id, int32_t pos_x_in, int32_t pos_y);

    void chequear_colisiones(std::vector<bloqueEscenario>& bloques,
                             std::vector<bloqueEscenario>& angulos) override;
    [[nodiscard]] EstadoEnemigo get_estado() const override;
    [[nodiscard]] int32_t get_puntos() const override;
    [[nodiscard]] bool esta_invertido() const override;
    void mover() override;
    void chocar_pared() override;
    [[nodiscard]] int32_t atacar() const override;
    bool hacer_dano(int32_t puntos_dano) override;
    void revivir() override;
    void matar() override;

    int32_t get_pos_x() override;
    int32_t get_pos_y() override;
    int32_t get_ancho() override;
    int32_t get_alto() override;

    [[nodiscard]] EnemigoDTO crear_dto() const override;
};


#endif  // MURCIELAGO_H
