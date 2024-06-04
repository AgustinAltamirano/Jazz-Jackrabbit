#include "menu_selec_jugador.h"
#include "constantes_menu.h"


MenuSeleccionJugador::MenuSeleccionJugador(QMainWindow* parent, MenuJuego& juego):
        MenuSeleccion(parent),
        juego(juego),
        central_widget(this),
        horizontal_layout_widget(&central_widget),
        horizontalLayout(&horizontal_layout_widget),
        jazz_player(this, NUM_JAZZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        spaz_player(this, NUM_SPAZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        lori_player(this, NUM_LORI_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER)
{
    setCentralWidget(&central_widget);

    horizontal_layout_widget.setGeometry(
            QRect(M_LEFT_PLAYER, M_TOP_PLAYER, ANCHO_PANTALLA, ALTO_PANTALLA));

    horizontalLayout.setSpacing(ESPACIADO_ENTRE_JUGADORES);
    horizontalLayout.setContentsMargins(M_LEFT, M_TOP, M_RIGHT, M_BOTTOM);

    conectar_botones({&jazz_player, &spaz_player, &lori_player},
                     {NUM_JAZZ_PLAYER, NUM_SPAZ_PLAYER, NUM_LORI_PLAYER}, horizontalLayout);
}


void MenuSeleccionJugador::realizar_accion_menu(int boton_seleccionado) {
    juego.definir_personaje_elegido(boton_seleccionado);

    // Tenemos que ver cómo hacer para saber cuál de las dos elegir
    juego.crear_partida();
    juego.unir_partida();

    close();
}
