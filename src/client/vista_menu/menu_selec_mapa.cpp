#include "menu_selec_mapa.h"

#include <QMessageBox>
#include <string>
#include <unordered_map>

#include "constantes_menu.h"
#include "menu_principal.h"


const std::unordered_map<TipoEscenario, std::string> MenuSeleccionMapa::MAPA_TIPO_ESCENARIO{
        {ESCENARIO_CASTLE, "castle"}, {ESCENARIO_CARROTUS, "carrotus"}, {ESCENARIO_INDEFINIDO, ""}};


MenuSeleccionMapa::MenuSeleccionMapa(QMainWindow* parent, MenuJuego& juego):
        MenuSeleccion(parent),
        juego(juego),
        selector_jugador(this, juego, true),
        popup_nombre_mapa(this),
        central_widget(this),
        vertical_layout_widget(&central_widget),
        vertical_layout(&vertical_layout_widget),
        opcion_mapa_1(this, &central_widget, NUM_MAPA_1, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),
        opcion_mapa_2(this, &central_widget, NUM_MAPA_2, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),
        opcion_mapa_custom(this, &central_widget, NUM_MAPA_CUST, ANCHO_BTN_MAPA, ALTO_BTN_MAPA) {
    setCentralWidget(&central_widget);

    vertical_layout_widget.setGeometry(
            QRect(M_LEFT_LAYOUT, M_TOP_LAYOUT, ANCHO_PANTALLA, ALTO_PANTALLA));

    vertical_layout.setSpacing(ESPACIADO_ENTRE_MAPAS);
    vertical_layout.setContentsMargins(M_LEFT_MAPA, M_TOP_MAPA, M_RIGHT_MAPA, M_BOTTOM_MAPA);

    connect(&opcion_mapa_custom, &QPushButton::clicked, this, &MenuSeleccionMapa::desplegar_popup);

    conectar_botones({&opcion_mapa_1, &opcion_mapa_2}, {ESCENARIO_CASTLE, ESCENARIO_CARROTUS},
                     vertical_layout);

    vertical_layout.addWidget(&opcion_mapa_custom);
}


void MenuSeleccionMapa::realizar_accion_menu(QPushButton* boton_seleccionado) {
    auto opcion_seleccionada = boton_seleccionado->property(KEY_TIPO_BOTON).value<TipoEscenario>();
    juego.definir_mapa_elegido(MAPA_TIPO_ESCENARIO.at(opcion_seleccionada));
    selector_jugador.move(this->pos());
    selector_jugador.show();
    hide();
}


void MenuSeleccionMapa::desplegar_popup() { popup_nombre_mapa.exec(); }


void MenuSeleccionMapa::validar_seleccion_mapa() {
    bool mapa_es_valido = true;
    // cppcheck-suppress knownConditionTrueFalse
    if (mapa_es_valido) {
        definir_mapa_custom();
    } else {
        QMessageBox::critical(this, "Mapa erróneo", "El mapa indicado no existe");
    }
}


void MenuSeleccionMapa::definir_mapa_custom() {
    juego.definir_mapa_elegido(popup_nombre_mapa.obtener_seleccion_mapa());
    selector_jugador.move(this->pos());
    selector_jugador.show();
    hide();
}
