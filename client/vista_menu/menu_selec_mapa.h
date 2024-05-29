#ifndef MENU_SELEC_MAPA_H
#define MENU_SELEC_MAPA_H


#include <QHBoxLayout>

#include "boton_animado.h"
#include "boton_menu.h"

#define NUM_MAPA_1 3
#define NUM_MAPA_2 4
#define NUM_MAPA_CUST 5

#define M_LEFT_LAYOUT 0
#define M_TOP_LAYOUT 0

#define ESPACIADO_ENTRE_MAPAS 100
#define M_LEFT_MAPA 150
#define M_TOP_MAPA 150
#define M_RIGHT_MAPA 0
#define M_BOTTOM_MAPA 150


class MenuSeleccionMapa : public QMainWindow {
private:
    QWidget central_widget;

    QWidget vertical_layout_widget;

    QVBoxLayout vertical_layout;

    BotonAnimado opcion_mapa_1;

    BotonAnimado opcion_mapa_2;

    BotonAnimado opcion_mapa_custom;

public:
    explicit MenuSeleccionMapa(QMainWindow* parent);
};


#endif  // MENU_SELEC_MAPA_H
