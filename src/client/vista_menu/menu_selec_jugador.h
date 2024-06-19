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
#define MSJ_BOX_CREACION_PARTIDA "Código de partida: "
#define MSJ_BOX_FALLO_PARTIDA "La partida está llena o no existe"
#define TITULO_CREACION_PARTIDA "Partida creada"
#define TITULO_FALLO_PARTIDA "No se pudo unir a la partida"


class MenuSeleccionJugador: public MenuSeleccion {
private:
    MenuJuego& juego;

    bool es_de_creacion;

    QWidget central_widget;

    QWidget horizontal_layout_widget;

    QHBoxLayout horizontalLayout;

    BotonAnimadoJugador jazz_player;

    BotonAnimadoJugador spaz_player;

    BotonAnimadoJugador lori_player;

protected:
    void realizar_accion_menu(QPushButton* boton_seleccionado) override;

public:
    explicit MenuSeleccionJugador(QMainWindow* parent, MenuJuego& juego, bool config);
};


#endif  // MENU_SELEC_JUGADOR_H
