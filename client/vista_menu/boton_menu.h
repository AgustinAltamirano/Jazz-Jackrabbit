#ifndef BOTONMENU_H
#define BOTONMENU_H

#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>

#define CANT_EFECTOS_SONIDO 6

class BotonMenu : public QPushButton {
private:
    QMediaPlayer reproductor_efectos;

    QMediaPlaylist efectos_de_sonido;

    void definir_efectos_de_sonido();

    void reproducir_efecto_sonido();

public:
    BotonMenu(QWidget* parent, int offset_x, int offset_y, int ancho, int alto, const char* text);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
};


#endif //BOTONMENU_H
