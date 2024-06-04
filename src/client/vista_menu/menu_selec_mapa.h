#ifndef MENU_SELEC_MAPA_H
#define MENU_SELEC_MAPA_H


#include <QHBoxLayout>

#include "boton_animado_mapa.h"
#include "boton_menu.h"
#include "menu_juego.h"

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


class MenuSeleccionMapa: public QMainWindow {
private:
    MenuJuego& juego;

    QMainWindow* menu_previo;

    QWidget central_widget;

    QWidget vertical_layout_widget;

    QVBoxLayout vertical_layout;

    BotonAnimadoMapa opcion_mapa_1;

    BotonAnimadoMapa opcion_mapa_2;

    BotonAnimadoMapa opcion_mapa_custom;

    QPushButton* boton_enfocado = nullptr;

    void conectar_botones();

    void mostrar_selector_jugador();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit MenuSeleccionMapa(QMainWindow* parent, MenuJuego& juego);
};


#endif  // MENU_SELEC_MAPA_H
