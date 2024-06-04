#include "menu_selec_mapa.h"

#include "constantes_menu.h"
#include "menu_selec_jugador.h"


MenuSeleccionMapa::MenuSeleccionMapa(QMainWindow* parent, MenuJuego& juego):
        QMainWindow(parent),
        juego(juego),
        central_widget(this),
        vertical_layout_widget(&central_widget),
        vertical_layout(&vertical_layout_widget),
        opcion_mapa_1(parent, &central_widget, NUM_MAPA_1, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),
        opcion_mapa_2(parent, &central_widget, NUM_MAPA_2, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),
        opcion_mapa_custom(parent, &central_widget, NUM_MAPA_CUST, ANCHO_BTN_MAPA, ALTO_BTN_MAPA) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    vertical_layout_widget.setGeometry(
            QRect(M_LEFT_LAYOUT, M_TOP_LAYOUT, ANCHO_PANTALLA, ALTO_PANTALLA));

    vertical_layout.setSpacing(ESPACIADO_ENTRE_MAPAS);
    vertical_layout.setContentsMargins(M_LEFT_MAPA, M_TOP_MAPA, M_RIGHT_MAPA, M_BOTTOM_MAPA);

    conectar_botones();

    vertical_layout.addWidget(&opcion_mapa_1);
    vertical_layout.addWidget(&opcion_mapa_2);
    vertical_layout.addWidget(&opcion_mapa_custom);

    setCentralWidget(&central_widget);
}


void MenuSeleccionMapa::conectar_botones() {
    // Defino los handlers de los botones
    connect(&opcion_mapa_1, &QPushButton::clicked, this,
            &MenuSeleccionMapa::mostrar_selector_jugador);
    connect(&opcion_mapa_2, &QPushButton::clicked, this,
            &MenuSeleccionMapa::mostrar_selector_jugador);
    connect(&opcion_mapa_custom, &QPushButton::clicked, this,
            &MenuSeleccionMapa::mostrar_selector_jugador);
}


void MenuSeleccionMapa::mostrar_selector_jugador() {
    auto* boton_mapa_seleccionado = dynamic_cast<QPushButton*>(sender());
    if (boton_mapa_seleccionado == boton_enfocado) {
        auto* selector_jugador = new MenuSeleccionJugador(this, juego);
        selector_jugador->move(this->pos());
        selector_jugador->show();
        hide();
    }
    boton_enfocado = boton_mapa_seleccionado;
}
