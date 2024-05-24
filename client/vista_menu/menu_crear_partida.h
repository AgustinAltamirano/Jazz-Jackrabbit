#ifndef MENUCREARPARTIDA_H
#define MENUCREARPARTIDA_H

#include <QLabel>
#include <QMainWindow>
#include "boton_menu.h"

#define POS_MULTIPLAYER_BTN 0
#define WIDTH_MULTIPLAYER_BTN 400
#define TEXT_MULTIPLAYER_BTN "MULTIPLAYER"


class MenuCrearPartida : public QMainWindow {
private:
    QLabel label;

    BotonMenu multiplayer_btn;
public:
    explicit MenuCrearPartida(QMainWindow *parent, QFont &fuente);
};


#endif  // MENUCREARPARTIDA_H
