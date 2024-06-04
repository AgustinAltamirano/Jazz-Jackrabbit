#ifndef MENUCREARPARTIDA_H
#define MENUCREARPARTIDA_H

#include <QLabel>
#include <QMainWindow>

#include "boton_menu.h"
#include "constantes_menu.h"
#include "menu_juego.h"
#include "menu_selec_jugador.h"
#include "menu_selec_mapa.h"
#include "ventana_dialogo.h"

class MenuCrearPartida: public QMainWindow {
private:
    MenuJuego& juego;

    VentanaDialogo popup_cant_jugadores;

    QLabel label;

    BotonMenu multiplayer_btn;

    MenuSeleccionMapa menu_seleccion_mapa;

    void desplegar_popup();

public:
    explicit MenuCrearPartida(QMainWindow* parent, MenuJuego& juego);

    void crear_partida();
};


#endif  // MENUCREARPARTIDA_H
