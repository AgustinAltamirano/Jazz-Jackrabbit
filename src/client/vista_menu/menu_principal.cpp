#include "menu_principal.h"

#include "menu_juego.h"


MenuPrincipal::MenuPrincipal(QMainWindow* parent, MenuJuego& juego):
        QMainWindow(parent),
        juego(juego),
        popup_cod_partida(this),
        new_game_btn(this, OFFSET_X_NEWGAME_BTN, OFFSET_Y_NEWGAME_BTN, ANCHO_NEWGAME_BTN,
                     ALTO_NEWGAME_BTN, TEXTO_NEWGAME_BTN),

        join_game_btn(this, OFFSET_X_JOINGAME_BTN, OFFSET_Y_JOINGAME_BTN, ANCHO_JOINGAME_BTN,
                      ALTO_JOINGAME_BTN, TEXTO_JOINGAME_BTN) {
    setWindowTitle(TITULO_VENTANAS);
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    QString estilo = QString("QMainWindow {background-image: url(%1);}").arg(QString(ASSETS_PATH) + RUTA_IMG_INICIAL);
    setStyleSheet(estilo);
    conectar_botones();
}


void MenuPrincipal::conectar_botones() {
    // Defino los handlers de los botones
    connect(&new_game_btn, &QPushButton::clicked, this, &MenuPrincipal::crear_partida);
    connect(&join_game_btn, &QPushButton::clicked, this,
            &MenuPrincipal::desplegar_popup);
}


void MenuPrincipal::crear_partida() {
    auto menu_crear_partida = new MenuCrearPartida(this, juego);
    menu_crear_partida->move(this->pos());
    menu_crear_partida->show();
    hide();
}


void MenuPrincipal::desplegar_popup() {
    popup_cod_partida.exec();
}


void MenuPrincipal::unirse_partida() {
    juego.definir_codigo_partida(popup_cod_partida.obtener_seleccion());
    auto menu_seleccion_jug = new MenuSeleccionJugador(this, juego);
    menu_seleccion_jug->move(this->pos());
    menu_seleccion_jug->show();
    hide();
}


void MenuPrincipal::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        this->close();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
