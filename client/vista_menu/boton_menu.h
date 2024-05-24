#ifndef BOTONMENU_H
#define BOTONMENU_H

#include <QKeyEvent>
#include "constantes_menu.h"

class BotonMenu : public QPushButton {
private:
    QMediaPlayer reproductor_efectos;

    QMediaPlaylist efectos_de_sonido;

    void definir_efectos_de_sonido();

    void reproducir_efecto_sonido();

public:
    BotonMenu(QWidget *parent, int posicion_en_widget, int ancho, const char *text);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
};


#endif //BOTONMENU_H
