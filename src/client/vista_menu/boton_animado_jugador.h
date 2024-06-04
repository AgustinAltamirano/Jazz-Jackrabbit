#ifndef BOTON_ANIMADO_JUGADOR_H
#define BOTON_ANIMADO_JUGADOR_H


#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "boton_menu.h"
#include "sprites_jugador.h"


class BotonAnimadoJugador: public BotonMenu {
public:
    BotonAnimadoJugador(QMainWindow* parent, int num_sprite, int ancho, int alto);

protected:
    void focusInEvent(QFocusEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;

private:
    QLabel label_jugador;

    QLabel label_nombre;

    SpritesJugador manejador_sprites;

    void paintEvent(QPaintEvent* event) override;
};

#endif  // BOTON_ANIMADO_JUGADOR_H
