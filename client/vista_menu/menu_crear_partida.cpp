#include "menu_crear_partida.h"

#include <QBitmap>

#include "ventana_inicial.h"


MenuCrearPartida::MenuCrearPartida(QMainWindow* parent, QFont& fuente) :
        QMainWindow(parent),
        multiplayer_btn(this, POS_MULTIPLAYER_BTN, WIDTH_MULTIPLAYER_BTN, TEXT_MULTIPLAYER_BTN, fuente),
        label(this)
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);

    multiplayer_btn.setGeometry(QRect(20, 215, WIDTH_MULTIPLAYER_BTN, 51));
    multiplayer_btn.clearFocus();

    QPixmap pixmap(":/img/img/multiplayer.png");
    QRgb colorKey = qRgb(0, 128, 255);
    QBitmap mask = pixmap.createMaskFromColor(colorKey, Qt::MaskInColor);
    pixmap.setMask(mask);

    label.setPixmap(pixmap.scaled(180, 180, Qt::KeepAspectRatio));
    label.setGeometry(QRect(30 + WIDTH_MULTIPLAYER_BTN, 150, 180, 180));
}
