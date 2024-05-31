#ifndef BOTON_ANIMADO_MAPA_H
#define BOTON_ANIMADO_MAPA_H


#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "boton_menu.h"
#include "sprites_mapa.h"


class BotonAnimadoMapa: public BotonMenu {
    Q_OBJECT

public:
    BotonAnimadoMapa(QMainWindow* parent, QWidget* widget, int num_sprite, int ancho, int alto);

protected:
    void focusInEvent(QFocusEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;

private:
    QLabel label_jugador;

    SpritesMapa manejador_sprites;

    void paintEvent(QPaintEvent* event) override;
};

#endif  // BOTON_ANIMADO_MAPA_H
