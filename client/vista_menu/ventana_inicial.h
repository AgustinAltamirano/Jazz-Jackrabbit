#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include "menu_principal.h"

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480


class VentanaInicial : public QMainWindow {
private:
    QPushButton press_click_btn;

    QFont fuente_juego;

    QMediaPlayer reproductor_musica;

    QMediaPlaylist playlist;

    MenuPrincipal *menu_principal;

    void definir_fuentes();

    void mostrar_menu_principal();

    void reproducir_musica();

    void inicializar_boton();

public:
    explicit VentanaInicial();

    ~VentanaInicial() override;
};

#endif // VENTANAPRINCIPAL_H
