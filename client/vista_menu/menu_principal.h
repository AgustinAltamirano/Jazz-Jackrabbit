#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "menu_crear_partida.h"

class MenuPrincipal : public QMainWindow {
private:
    BotonMenu new_game_btn;

    BotonMenu join_game_btn;

    MenuCrearPartida menu_crear_partida;

    void conectar_botones();

    void mostrar_menu_crear_partida();

    void mostrar_menu_unirse_partida();

public:
    explicit MenuPrincipal();
};


#endif //MENUPRINCIPAL_H
