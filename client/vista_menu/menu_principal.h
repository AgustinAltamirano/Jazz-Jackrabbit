#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QPushButton>
#include <QMainWindow>
#include <QButtonGroup>
#include "boton_menu.h"

enum PosicionBoton {
    POS_NEWGAME_BTN,
    POS_JOINGAME_BTN,
    POS_EDITOR_BTN
};

#define WIDTH_NEWGAME_BTN 290
#define TEXT_NEWGAME_BTN "NEW GAME"
#define WIDTH_JOINGAME_BTN 321
#define TEXT_JOINGAME_BTN "JOIN GAME"
#define WIDTH_EDITOR_BTN 391
#define TEXT_EDITOR_BTN "EDITOR MODE"


class VentanaInicial;  // Declaración adelantada

class MenuPrincipal : public QMainWindow {
private:
    BotonMenu new_game_btn;

    BotonMenu join_game_btn;

    BotonMenu editor_mode_btn;

    void conectar_botones();

    void mostrar_menu_crear_partida();

    void mostrar_menu_unirse_partida();

    void mostrar_menu_editor();

public:
    explicit MenuPrincipal(QFont &fuente);
};


#endif //MENUPRINCIPAL_H
