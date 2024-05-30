#include "menu_selec_jugador.h"

#include <QHBoxLayout>

#include "boton_animado.h"
#include "constantes_menu.h"


MenuSeleccionJugador::MenuSeleccionJugador(QMainWindow* parent):
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

    conectar_botones();

    horizontalLayout.addWidget(&jazz_player);
    horizontalLayout.addWidget(&spaz_player);
    horizontalLayout.addWidget(&lori_player);

    setCentralWidget(&central_widget);
}


void MenuSeleccionJugador::conectar_botones() {
    // Defino los handlers de los botones
    connect(&jazz_player, &QPushButton::clicked, this,
            &MenuSeleccionJugador::mostrar_selector_mapa);
    connect(&spaz_player, &QPushButton::clicked, this,
            &MenuSeleccionJugador::mostrar_selector_mapa);
    connect(&lori_player, &QPushButton::clicked, this,
            &MenuSeleccionJugador::mostrar_selector_mapa);
}


void MenuSeleccionJugador::mostrar_selector_mapa() {
    auto* boton_pj_seleccionado = dynamic_cast<QPushButton*>(sender());
    if (boton_pj_seleccionado == boton_enfocado) {
        auto* selector_mapa = new MenuSeleccionMapa(this);
        selector_mapa->move(this->pos());
        selector_mapa->show();
        hide();
    }
    boton_enfocado = dynamic_cast<QPushButton*>(sender());
}
