#include "menu_selec_jugador.h"

#include <QHBoxLayout>

#include "boton_animado_jugador.h"
#include "constantes_menu.h"
#include "menu_juego.h"


MenuSeleccionJugador::MenuSeleccionJugador(QMainWindow* parent, MenuJuego& juego):
        QMainWindow(parent),
        central_widget(this),
        horizontal_layout_widget(&central_widget),
        horizontalLayout(&horizontal_layout_widget),
        jazz_player(this, NUM_JAZZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        spaz_player(this, NUM_SPAZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        lori_player(this, NUM_LORI_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    horizontal_layout_widget.setGeometry(
            QRect(M_LEFT_PLAYER, M_TOP_PLAYER, ANCHO_PANTALLA, ALTO_PANTALLA));

    horizontalLayout.setSpacing(ESPACIADO_ENTRE_JUGADORES);
    horizontalLayout.setContentsMargins(M_LEFT, M_TOP, M_RIGHT, M_BOTTOM);

    horizontalLayout.addWidget(&jazz_player);
    horizontalLayout.addWidget(&spaz_player);
    horizontalLayout.addWidget(&lori_player);

    setCentralWidget(&central_widget);
}
