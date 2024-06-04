#ifndef MENUCREARPARTIDA_H
#define MENUCREARPARTIDA_H

#include <QLabel>
#include <QMainWindow>

#include "boton_menu.h"
#include "constantes_menu.h"
#include "menu_juego.h"
#include "menu_selec_jugador.h"
#include "menu_selec_mapa.h"

class MenuCrearPartida: public QMainWindow {
private:
    MenuJuego& juego;

    QLabel label;

    BotonMenu multiplayer_btn;

    MenuSeleccionMapa menu_seleccion_mapa;

    void mostrar_menu_crear_partida();

public:
    explicit MenuCrearPartida(QMainWindow* parent);
    explicit MenuCrearPartida(QMainWindow* parent, MenuJuego& juego);
};


#endif  // MENUCREARPARTIDA_H
