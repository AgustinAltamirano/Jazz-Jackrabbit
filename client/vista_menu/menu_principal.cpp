#include <sstream>
#include "menu_principal.h"
#include "ventana_inicial.h"


MenuPrincipal::MenuPrincipal(QFont &fuente) :
        QMainWindow(),
        new_game_btn(this, POS_NEWGAME_BTN, WIDTH_NEWGAME_BTN, TEXT_NEWGAME_BTN, fuente),
        join_game_btn(this, POS_JOINGAME_BTN, WIDTH_JOINGAME_BTN, TEXT_JOINGAME_BTN, fuente),
        editor_mode_btn(this, POS_EDITOR_BTN, WIDTH_EDITOR_BTN, TEXT_EDITOR_BTN, fuente)
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    setStyleSheet("QMainWindow {background-image: url(:/img/img/bgd_mainmenu.jpg);}");
    conectar_botones();
}


void MenuPrincipal::conectar_botones() {
    // Defino los handlers de los botones
    connect(&new_game_btn, &QPushButton::clicked,this,&MenuPrincipal::mostrar_menu_crear_partida);
    connect(&join_game_btn, &QPushButton::clicked,this,&MenuPrincipal::mostrar_menu_unirse_partida);
    connect(&editor_mode_btn, &QPushButton::clicked,this,&MenuPrincipal::mostrar_menu_editor);
}


void MenuPrincipal::mostrar_menu_crear_partida() {
    // menu_crear_partida = new MenuCrearPartida(this, fuente_juego);
    // menu_crear_partida->show();
    hide();
}


void MenuPrincipal::mostrar_menu_unirse_partida() {
    // menu_unirse_partida = new MenuUnirsePartida(this, fuente_juego);
    // menu_unirse_partida->show();
    hide();
}


void MenuPrincipal::mostrar_menu_editor() {
    // menu_editor_partida = new MenuEditorPartida(this, fuente_juego);
    // menu_editor_partida->show();
    hide();
}