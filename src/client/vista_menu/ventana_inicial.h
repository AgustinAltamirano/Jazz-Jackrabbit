#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include "menu_juego.h"
#include "menu_principal.h"

QFont obtener_fuente();

class VentanaInicial: public QMainWindow {
private:
    QPushButton press_click_btn;

    QMediaPlayer reproductor_musica;

    QMediaPlaylist playlist;

    MenuPrincipal menu_principal;

    void mostrar_menu_principal();

    void reproducir_musica();

    void inicializar_boton();

public:
    explicit VentanaInicial(MenuJuego& juego);
};

#endif  // VENTANAPRINCIPAL_H
