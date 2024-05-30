#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H


#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "boton_menu.h"
#include "sprites_jugador.h"


class BotonAnimado: public BotonMenu {
    Q_OBJECT

public:
    BotonAnimado(QMainWindow* parent, int num_sprite, int ancho, int alto);

protected:
    void focusInEvent(QFocusEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;

private:
    QLabel label_jugador;

    QLabel label_nombre;

    SpritesJugador manejador_sprites;

    void paintEvent(QPaintEvent* event) override;
};

#endif  // SPRITEANIMATION_H
