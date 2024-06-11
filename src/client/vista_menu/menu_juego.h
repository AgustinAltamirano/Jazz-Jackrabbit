#ifndef MENU_JUEGO_H
#define MENU_JUEGO_H


#include "../lobby/lobby.h"


class MenuJuego {
public:
    MenuJuego(int argc, char* argv[], Lobby& lobby);

    void definir_mapa_elegido(const std::string& mapa);

    void definir_personaje_elegido(TipoPersonaje personaje);

    void definir_cant_jugadores(int cant_jug);

    void crear_partida();

    void unir_partida();

    void definir_codigo_partida(int cod_partida);

private:
    Lobby& lobby;

    TipoPersonaje personaje_elegido;

    std::string mapa_elegido;

    int cant_jugadores;

    int codigo_partida;
};


#endif  // MENU_JUEGO_H
