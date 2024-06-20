#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../../common/estado_personaje.h"
#include "../../common/snapshot_dto.h"
#include "../../common/tipo_arma.h"
#include "../../common/tipo_comando.h"
#include "../../common/tipo_personaje.h"
#include "assets/recogible.h"

class personaje {
private:
    const int32_t spawn_x;
    const int32_t spawn_y;

    int32_t id;
    TipoPersonaje tipo_de_personaje;
    int32_t alto;
    int32_t ancho;

    int32_t pos_x;
    int vel_x;

    bool mover_izq;
    bool mover_der;

    int32_t pos_y;
    int vel_y;
    int aceleracion_y;  // gravedad

    bool dash;
    bool de_espaldas;      // invertido en eje x
    bool en_aire;          // define si la aceleracion vertical y horizontal afecta o no
    bool ataque_especial;  // si está realizando un ataque especial las hitboxes hacen daño a los
                           // enemigos

    EstadoPersonaje estado;  // (enum con el tipo de estado del personaje)
    int tiempo_estado;       // (integer contador de cuanto tiempo lleva un personaje en un estado)

    int vida;
    int puntos;

    TipoArma arma_actual;
    std::map<TipoArma, int32_t> inventario_balas;
    uint32_t tiempo_recarga;  // frames antes de poder disparar

public:
    personaje(int32_t id, TipoPersonaje tipo, int32_t pos_x_inicial, int32_t pos_y_inicial);

    bool ejecutar_accion(const std::vector<TipoComando>& teclas);  // chequea estado y decide si
                                                                   // moverse, CAMBIA LA VELOCIDAD
    void cambiar_posicion(int32_t x,
                          int32_t y);  // despues de revisar colisiones se efectua el cambio real
    void cambiar_estado(bool cae);
    void pasar_tick();
    void recoger_objeto(int32_t valor, TipoRecogible tipo);
    [[nodiscard]] bool en_ataque_especial() const;

    // los siguientes dos métodos sirven para el chqueo de colisiones
    // Ayuda a decidir con que pared choca el personaje.
    [[nodiscard]] std::vector<int32_t> get_pos_actual() const;
    [[nodiscard]] std::vector<int32_t> get_pos_a_ir() const;
    [[nodiscard]] int32_t get_ancho() const;
    [[nodiscard]] int32_t get_alto() const;

    // efectos de gravedad
    void efectuar_gravedad();
    void dejar_de_caer();

    [[nodiscard]] TipoArma get_arma() const;
    [[nodiscard]] bool get_invertido() const;
    void disparar(int32_t frames_recarga);
    bool efectuar_dano(int32_t dano);
    void dar_puntos(int32_t puntos);

    // funcion para la construccion del dto
    [[nodiscard]] ClienteDTO crear_dto() const;
};

#endif  // PERSONAJE_H
