#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QPushButton>

#include "boton_menu.h"
#include "menu_crear_partida.h"

enum PosicionBoton {
    POS_NEWGAME_BTN,
    POS_JOINGAME_BTN,
};

#define WIDTH_NEWGAME_BTN 290
#define TEXT_NEWGAME_BTN "NEW GAME"
#define WIDTH_JOINGAME_BTN 321
#define TEXT_JOINGAME_BTN "JOIN GAME"

class VentanaInicial;  // Declaración adelantada

class MenuPrincipal : public QMainWindow {
private:
    BotonMenu new_game_btn;

    BotonMenu join_game_btn;

    MenuCrearPartida menu_crear_partida;

    void conectar_botones();

    void mostrar_menu_crear_partida();

    void mostrar_menu_unirse_partida();

public:
    explicit MenuPrincipal(QFont &fuente);
};


#endif //MENUPRINCIPAL_H
