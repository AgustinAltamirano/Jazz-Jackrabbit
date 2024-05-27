#include "menu_principal.h"


MenuPrincipal::MenuPrincipal() :
        QMainWindow(),
        new_game_btn(this,
                     OFFSET_X_NEWGAME_BTN,
                     OFFSET_Y_NEWGAME_BTN,
                     ANCHO_NEWGAME_BTN,
                     ALTO_NEWGAME_BTN,
                     TEXTO_NEWGAME_BTN
                     ),

        join_game_btn(this,
                      OFFSET_X_JOINGAME_BTN,
                      OFFSET_Y_JOINGAME_BTN,
                      ANCHO_JOINGAME_BTN,
                      ALTO_JOINGAME_BTN,
                      TEXTO_JOINGAME_BTN
                      ),

        menu_crear_partida(this)
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    QString estilo = QString("QMainWindow {background-image: url(%1);}").arg(RUTA_IMG_INICIAL);
    setStyleSheet(estilo);
    conectar_botones();
}


void MenuPrincipal::conectar_botones() {
    // Defino los handlers de los botones
    connect(&new_game_btn, &QPushButton::clicked,this,&MenuPrincipal::mostrar_menu_crear_partida);
    connect(&join_game_btn, &QPushButton::clicked,this,&MenuPrincipal::mostrar_menu_unirse_partida);
}


void MenuPrincipal::mostrar_menu_crear_partida() {
    menu_crear_partida.show();
    hide();
}


void MenuPrincipal::mostrar_menu_unirse_partida() {
    // menu_unirse_partida = new MenuUnirsePartida(this, fuente_juego);
    // menu_unirse_partida->show();
    hide();
}
