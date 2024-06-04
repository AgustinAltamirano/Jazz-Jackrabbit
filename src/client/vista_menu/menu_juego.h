#ifndef MENU_JUEGO_H
#define MENU_JUEGO_H


#include "../lobby/lobby.h"


class MenuJuego {
public:
    MenuJuego(int argc, char* argv[], Lobby& lobby);

    void definir_mapa(int mapa);

    void definir_personaje(int personaje);

    void definir_cant_jugadores(int8_t cant_jugadores);

    void crear_partida();

    void unir_partida();

    void definir_codigo_partida(int cod_partida);

private:
    Lobby& lobby;

    int personaje_elegido;

    int mapa_elegido;

    int8_t cant_jugadores_elegidos;

    int codigo_partida;
};


#endif  // MENU_JUEGO_H
