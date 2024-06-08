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


class MenuSeleccionMapa: public MenuSeleccion {
private:
    MenuJuego& juego;

    QWidget central_widget;

    QWidget vertical_layout_widget;

    QVBoxLayout vertical_layout;

    BotonAnimadoMapa opcion_mapa_1;

    BotonAnimadoMapa opcion_mapa_2;

    BotonAnimadoMapa opcion_mapa_custom;

protected:
    void realizar_accion_menu(int boton_seleccionado) override;

public:
    explicit MenuSeleccionMapa(QMainWindow* parent, MenuJuego& juego);
};


#endif  // MENU_SELEC_MAPA_H
