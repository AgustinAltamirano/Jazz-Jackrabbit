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
    QPixmap pixmap(RUTA_IMG_MENU_MULTIPLAYER);
    QRgb colorKey = qRgb(R_MULTIPLAYER, G_MULTIPLAYER, B_MULTIPLAYER);
    QBitmap mask = pixmap.createMaskFromColor(colorKey, Qt::MaskInColor);
    pixmap.setMask(mask);

    label.setPixmap(pixmap.scaled(TAM_IMG_MULTIPLAYER, TAM_IMG_MULTIPLAYER, Qt::KeepAspectRatio));
    label.setGeometry(QRect(OFFSET_X_IMG_MULTIPLAYER_BTN + ANCHO_MULTIPLAYER_BTN,
                            OFFSET_Y_IMG_MULTIPLAYER_BTN,
                            TAM_IMG_MULTIPLAYER,
                            TAM_IMG_MULTIPLAYER));
}
