#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "menu_crear_partida.h"
#include "menu_juego.h"
#include "ventana_dialogo.h"


class MenuPrincipal: public QMainWindow {
private:
    MenuJuego& juego;

    MenuCrearPartida menu_crear_partida;

    MenuSeleccionJugador menu_seleccion_jug;

    VentanaDialogo popup_cod_partida;

    BotonMenu new_game_btn;

    BotonMenu join_game_btn;

    void conectar_botones();

    void desplegar_popup();

    void crear_partida();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit MenuPrincipal(QMainWindow* parent, MenuJuego& juego);

    void unirse_partida();
};


#endif  // MENUPRINCIPAL_H
