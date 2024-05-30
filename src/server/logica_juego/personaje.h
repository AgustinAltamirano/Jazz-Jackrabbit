#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <string>
#include <vector>

class personaje {
private:
    int id;
    int tipo_de_personaje;  // indica si el personaje es Jazz, Lori o Spaz (cambiable a string)
    int alto;
    int ancho;

    int pos_x;
    int vel_x;
    int aceleracion_x;

    int pos_y;
    int vel_y;
    int aceleracion_y;  // gravedad

    int angulo;
    bool sobre_rampa;

    bool de_espaldas;      // invertido en eje x
    bool en_aire;          // define si la aceleracion vertical y horizontal afecta o no
    bool ataque_especial;  // si está realizando un ataque especial las hitboxes hacen daño a los
                           // enemigos

    // Estado estado (struct con el tipo de estado del personaje)
    // int contador de estado (integer contador de cuanto tiempo lleva un personaje en un estado)

    int vida;
    int puntos;

    // int arma_actual;
    // inventario inventario; (struct que mantiene el dato de que armas tiene y cuantas balas por
    // arma)
public:
    personaje(int id, int tipo, int pos_x_inicial, int pos_y_inicial);

    void cambiar_velocidad(
            const std::vector<std::string>&
                    teclas);  // chequea el estado y decide si puede moverse, CAMBIA LA VELOCIDAD
    void cambiar_posicion(int x, int y);  // despues de revisar colisiones se efectua el cambio real

    // los siguientes dos métodos sirven para el chqueo de colisiones
    // Ayuda a decidir con que pared choca el personaje.
    [[nodiscard]] std::vector<int> get_pos_actual() const;
    [[nodiscard]] std::vector<int> get_pos_a_ir() const;
    [[nodiscard]] int get_ancho() const;
    [[nodiscard]] int get_alto() const;

    // bool cambiar_estado(int estado);

    // bool disparar();
    // bool cambiar_arma();
    // bool efectuar_dano();
    // bool respawnear();
};


#endif  // PERSONAJE_H
