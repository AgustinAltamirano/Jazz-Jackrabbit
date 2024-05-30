#ifndef MENUCREARPARTIDA_H
#define MENUCREARPARTIDA_H

#include <QLabel>
#include <QMainWindow>

#include "boton_menu.h"
#include "constantes_menu.h"
#include "menu_selec_jugador.h"

class MenuCrearPartida: public QMainWindow {
private:
    QLabel label;

    BotonMenu multiplayer_btn;

    MenuSeleccionJugador menu_seleccion_jug;

    void mostrar_menu_crear_partida();

public:
    explicit MenuCrearPartida(QMainWindow* parent);
};


#endif  // MENUCREARPARTIDA_H
