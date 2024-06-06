#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <cstdint>
#include <string>
#include <vector>

#include "../../client/vista_juego/accion_juego_dto.h"
#include "../../client/vista_juego/snapshot_dto.h"
#include "assets/bala.h"
#include "assets/balaInfinita.h"
#include "assets/bala_arma_1.h"
#include "assets/bala_arma_2.h"
#include "assets/bala_arma_3.h"
#include "assets/recogible.h"

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
    uint32_t tiempo_recarga;  // frames antes de poder disparar

public:
    personaje(int32_t id, TipoPersonaje tipo, int32_t pos_x_inicial, int32_t pos_y_inicial);

    bool ejecutar_acciones(const std::vector<AccionJuego>& teclas);

    void cambiar_posicion(uint32_t x,
                          uint32_t y);  // despues de revisar colisiones se efectua el cambio real
    void cambiar_estado(bool cae);
    void pasar_tick();
    void recoger_objeto(uint32_t valor, TipoRecogible tipo);

    // los siguientes dos métodos sirven para el chqueo de colisiones
    // Ayuda a decidir con que pared choca el personaje.
    [[nodiscard]] std::vector<int32_t> get_pos_actual() const;
    [[nodiscard]] std::vector<int32_t> get_pos_a_ir() const;
    [[nodiscard]] uint32_t get_ancho() const;
    [[nodiscard]] uint32_t get_alto() const;

    [[nodiscard]] ArmaActual get_arma() const;
    [[nodiscard]] bool get_invertido() const;
    void disparar(uint32_t frames_recarga);
    // bool efectuar_dano();
    // bool respawnear();

    // funcion para la construccion del dto
    [[nodiscard]] ClienteDTO crear_dto() const;
};


#endif  // PERSONAJE_H
