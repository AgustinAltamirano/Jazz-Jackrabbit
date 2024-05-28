#ifndef MENU_SELEC_JUGADOR_H
#define MENU_SELEC_JUGADOR_H


#include <QHBoxLayout>

#include "boton_animado.h"
#include "boton_menu.h"
#include "menu_selec_mapa.h"

#define NUM_JAZZ_PLAYER 0
#define NUM_SPAZ_PLAYER 1
#define NUM_LORI_PLAYER 2

#define M_LEFT_PLAYER 0
#define M_TOP_PLAYER 0

#define ESPACIADO_ENTRE_JUGADORES 50
#define M_LEFT 50
#define M_TOP 150
#define M_RIGHT 0
#define M_BOTTOM 0


class MenuSeleccionJugador : public QMainWindow {
private:
    QWidget central_widget;

    QWidget horizontal_layout_widget;

    QHBoxLayout horizontalLayout;

    BotonAnimado jazz_player;

    BotonAnimado spaz_player;

    BotonAnimado lori_player;

    MenuSeleccionMapa selector_mapa;

    QPushButton* boton_enfocado = nullptr;

    void conectar_botones();

    void mostrar_selector_mapa();

public:
    explicit MenuSeleccionJugador(QMainWindow* parent);
};


#endif  // MENU_SELEC_JUGADOR_H
