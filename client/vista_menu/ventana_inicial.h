#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480


class VentanaInicial : public QMainWindow {
private:
    QPushButton press_click_btn;

    QFont fuente_juego;

    QMediaPlayer reproductor_musica;

    QMediaPlaylist playlist;

    void definir_fuentes();

    void reproducir_musica();

    void inicializar_boton();

public:
    explicit VentanaInicial();
};

#endif // VENTANAPRINCIPAL_H
