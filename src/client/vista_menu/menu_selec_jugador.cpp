#include "menu_selec_jugador.h"

#include <QHBoxLayout>

#include "boton_animado_jugador.h"
#include "constantes_menu.h"
#include "menu_juego.h"


MenuSeleccionJugador::MenuSeleccionJugador(QMainWindow* parent, MenuJuego& juego):
        QMainWindow(parent),
        menu_previo(parent),
        juego(juego),
        central_widget(this),
        horizontal_layout_widget(&central_widget),
        horizontalLayout(&horizontal_layout_widget),
        jazz_player(this, NUM_JAZZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        spaz_player(this, NUM_SPAZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        lori_player(this, NUM_LORI_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER) {
    setWindowTitle(TITULO_VENTANAS);
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    horizontal_layout_widget.setGeometry(
            QRect(M_LEFT_PLAYER, M_TOP_PLAYER, ANCHO_PANTALLA, ALTO_PANTALLA));

    horizontalLayout.setSpacing(ESPACIADO_ENTRE_JUGADORES);
    horizontalLayout.setContentsMargins(M_LEFT, M_TOP, M_RIGHT, M_BOTTOM);

    horizontalLayout.addWidget(&jazz_player);
    horizontalLayout.addWidget(&spaz_player);
    horizontalLayout.addWidget(&lori_player);

    setCentralWidget(&central_widget);
    conectar_botones();

    jazz_player.setProperty(KEY_TIPO_BOTON, NUM_JAZZ_PLAYER);
    spaz_player.setProperty(KEY_TIPO_BOTON, NUM_SPAZ_PLAYER);
    lori_player.setProperty(KEY_TIPO_BOTON, NUM_LORI_PLAYER);
}


void MenuSeleccionJugador::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        boton_enfocado = nullptr;
        menu_previo->move(this->pos());
        menu_previo->show();
        hide();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}


void MenuSeleccionJugador::conectar_botones() {
    // Defino los handlers de los botones
    connect(&jazz_player, &QPushButton::clicked, this,
            &MenuSeleccionJugador::terminar);
    connect(&spaz_player, &QPushButton::clicked, this,
            &MenuSeleccionJugador::terminar);
    connect(&lori_player, &QPushButton::clicked, this,
            &MenuSeleccionJugador::terminar);
}


void MenuSeleccionJugador::terminar() {
    auto* boton_pj_seleccionado = dynamic_cast<QPushButton*>(sender());
    if (boton_pj_seleccionado == boton_enfocado) {
        boton_enfocado = nullptr;

        int pj_seleccionado = boton_pj_seleccionado->property(KEY_TIPO_BOTON).toInt();

        juego.definir_personaje_elegido(pj_seleccionado);

        close();
    }
    boton_enfocado = boton_pj_seleccionado;
}
