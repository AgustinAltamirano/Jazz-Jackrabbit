#ifndef MENUCREARPARTIDA_H
#define MENUCREARPARTIDA_H

#include <QLabel>
#include "boton_menu.h"

class MenuCrearPartida : public QMainWindow {
private:
    QLabel label;

    BotonMenu multiplayer_btn;
public:
    explicit MenuCrearPartida(QMainWindow *parent);
};


#endif  // MENUCREARPARTIDA_H
