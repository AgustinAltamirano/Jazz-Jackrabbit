#ifndef MENU_SELEC_JUGADOR_H
#define MENU_SELEC_JUGADOR_H


#include "boton_animado_jugador.h"
#include "menu_juego.h"
#include "menu_seleccion.h"

#define NUM_JAZZ_PLAYER 0
#define NUM_SPAZ_PLAYER 1
#define NUM_LORI_PLAYER 2

#define M_LEFT_PLAYER 0
#define M_TOP_PLAYER 0

#define ESPACIADO_ENTRE_JUGADORES 50
#define M_LEFT 50
#define M_TOP 150
#define M_RIGHT 50
#define M_BOTTOM 0


class MenuSeleccionJugador: public MenuSeleccion {
private:
    MenuJuego& juego;

    QWidget central_widget;

    QWidget horizontal_layout_widget;

    QHBoxLayout horizontalLayout;

    BotonAnimadoJugador jazz_player;

    BotonAnimadoJugador spaz_player;

    BotonAnimadoJugador lori_player;

protected:
    void realizar_accion_menu(int boton_seleccionado) override;

public:
    explicit MenuSeleccionJugador(QMainWindow* parent, MenuJuego& juego);
};


#endif  // MENU_SELEC_JUGADOR_H
