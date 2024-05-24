#include "menu_crear_partida.h"
#include <QBitmap>


MenuCrearPartida::MenuCrearPartida(QMainWindow* parent) :
        QMainWindow(parent),
        multiplayer_btn(this,
                        OFFSET_X_MULTIPLAYER_BTN,
                        OFFSET_Y_MULTIPLAYER_BTN,
                        ANCHO_MULTIPLAYER_BTN,
                        ALTO_MULTIPLAYER_BTN,
                        TEXTO_MULTIPLAYER_BTN
                        ),
        label(this)
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);

    // Coloco la imagen con un Color Key para que el fondo sea transparente
    QPixmap pixmap(":/img/img/multiplayer.png");
    QRgb colorKey = qRgb(0, 128, 255);
    QBitmap mask = pixmap.createMaskFromColor(colorKey, Qt::MaskInColor);
    pixmap.setMask(mask);

    label.setPixmap(pixmap.scaled(180, 180, Qt::KeepAspectRatio));
    label.setGeometry(QRect(30 + ANCHO_MULTIPLAYER_BTN, 150, 180, 180));
}
