#include "menu_principal.h"


MenuPrincipal::MenuPrincipal():
        QMainWindow(),
        new_game_btn(this, OFFSET_X_NEWGAME_BTN, OFFSET_Y_NEWGAME_BTN, ANCHO_NEWGAME_BTN,
                     ALTO_NEWGAME_BTN, TEXTO_NEWGAME_BTN),

        join_game_btn(this, OFFSET_X_JOINGAME_BTN, OFFSET_Y_JOINGAME_BTN, ANCHO_JOINGAME_BTN,
                      ALTO_JOINGAME_BTN, TEXTO_JOINGAME_BTN) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    QString estilo = QString("QMainWindow {background-image: url(%1);}").arg(QString(ASSETS_PATH) + RUTA_IMG_INICIAL);
    setStyleSheet(estilo);
    conectar_botones();
}


void MenuPrincipal::conectar_botones() {
    // Defino los handlers de los botones
    connect(&new_game_btn, &QPushButton::clicked, this, &MenuPrincipal::mostrar_menu_crear_partida);
    connect(&join_game_btn, &QPushButton::clicked, this,
            &MenuPrincipal::mostrar_menu_unirse_partida);
}


void MenuPrincipal::mostrar_menu_crear_partida() {
    auto menu_crear_partida = new MenuCrearPartida(this);
    menu_crear_partida->move(this->pos());
    menu_crear_partida->show();
    hide();
}


void MenuPrincipal::mostrar_menu_unirse_partida() {
    auto menu_seleccion_jug = new MenuSeleccionJugador(this);
    menu_seleccion_jug->move(this->pos());
    menu_seleccion_jug->show();
    hide();
}
