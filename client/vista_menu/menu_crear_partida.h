#ifndef MENUCREARPARTIDA_H
#define MENUCREARPARTIDA_H

#include <QLabel>
#include <QMainWindow>
#include "boton_menu.h"
#include "constantes_menu.h"

class MenuCrearPartida : public QMainWindow {
private:
    QLabel label;

    BotonMenu multiplayer_btn;
public:
    explicit MenuCrearPartida(QMainWindow *parent);
};


#endif  // MENUCREARPARTIDA_H
