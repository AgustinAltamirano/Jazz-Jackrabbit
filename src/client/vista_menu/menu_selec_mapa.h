#ifndef MENU_SELEC_MAPA_H
#define MENU_SELEC_MAPA_H


#include "boton_animado_mapa.h"
#include "menu_juego.h"
#include "menu_seleccion.h"

#define NUM_MAPA_1 3
#define NUM_MAPA_2 4
#define NUM_MAPA_CUST 5

#define M_LEFT_LAYOUT 0
#define M_TOP_LAYOUT 0

#define ESPACIADO_ENTRE_MAPAS 100
#define M_LEFT_MAPA 100
#define M_TOP_MAPA 150
#define M_RIGHT_MAPA 0
#define M_BOTTOM_MAPA 150

#include "menu_selec_jugador.h"
#include "ventana_dialogo.h"


class MenuSeleccionMapa: public MenuSeleccion {
private:
    static const std::unordered_map<TipoEscenario, std::string> MAPA_TIPO_ESCENARIO;

    MenuJuego& juego;

    MenuSeleccionJugador selector_jugador;

    VentanaDialogo popup_nombre_mapa;

    QWidget central_widget;

    QWidget vertical_layout_widget;

    QVBoxLayout vertical_layout;

    BotonAnimadoMapa opcion_mapa_1;

    BotonAnimadoMapa opcion_mapa_2;

    BotonAnimadoMapa opcion_mapa_custom;

    void desplegar_popup();

    void definir_mapa_custom();

protected:
    void realizar_accion_menu(QPushButton* boton_seleccionado) override;

public:
    explicit MenuSeleccionMapa(QMainWindow* parent, MenuJuego& juego);

    void validar_seleccion_mapa();
};


#endif  // MENU_SELEC_MAPA_H
