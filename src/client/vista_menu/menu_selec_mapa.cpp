#include "menu_selec_mapa.h"

#include "constantes_menu.h"
#include "menu_principal.h"


const std::unordered_map<TipoEscenario, std::string> MenuSeleccionMapa::MAPA_TIPO_ESCENARIO {
        {ESCENARIO1, "castle"},
        {ESCENARIO2, "carrotus"},
        {ESCENARIO_INDEFINIDO, ""}
};


MenuSeleccionMapa::MenuSeleccionMapa(QMainWindow* parent, MenuJuego& juego):
        MenuSeleccion(parent),
        juego(juego),
        selector_jugador(this, juego, true),
        central_widget(this),
        vertical_layout_widget(&central_widget),
        vertical_layout(&vertical_layout_widget),
        opcion_mapa_1(this, &central_widget, NUM_MAPA_1, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),
        opcion_mapa_2(this, &central_widget, NUM_MAPA_2, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),
        opcion_mapa_custom(this, &central_widget, NUM_MAPA_CUST, ANCHO_BTN_MAPA, ALTO_BTN_MAPA)
{
    setCentralWidget(&central_widget);

    vertical_layout_widget.setGeometry(
            QRect(M_LEFT_LAYOUT, M_TOP_LAYOUT, ANCHO_PANTALLA, ALTO_PANTALLA));

    vertical_layout.setSpacing(ESPACIADO_ENTRE_MAPAS);
    vertical_layout.setContentsMargins(M_LEFT_MAPA, M_TOP_MAPA, M_RIGHT_MAPA, M_BOTTOM_MAPA);

    conectar_botones({&opcion_mapa_1, &opcion_mapa_2, &opcion_mapa_custom},
                     {ESCENARIO1, ESCENARIO2, ESCENARIO_INDEFINIDO}, vertical_layout);
}


void MenuSeleccionMapa::realizar_accion_menu(QPushButton* boton_seleccionado) {
    auto opcion_seleccionada = boton_seleccionado->property(KEY_TIPO_BOTON).value<TipoEscenario>();
    juego.definir_mapa_elegido(MAPA_TIPO_ESCENARIO.at(opcion_seleccionada));
    selector_jugador.move(this->pos());
    selector_jugador.show();
    hide();
}
