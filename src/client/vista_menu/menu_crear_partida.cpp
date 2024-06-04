#include "menu_crear_partida.h"

#include <QBitmap>

#include "boton_animado_jugador.h"
#include "menu_juego.h"


MenuCrearPartida::MenuCrearPartida(QMainWindow* parent, MenuJuego& juego):
        QMainWindow(parent),
        juego(juego),
        popup_cant_jugadores(this),
        multiplayer_btn(this, OFFSET_X_MULTIPLAYER_BTN, OFFSET_Y_MULTIPLAYER_BTN,
                        ANCHO_MULTIPLAYER_BTN, ALTO_MULTIPLAYER_BTN, TEXTO_MULTIPLAYER_BTN),
        label(this),
        menu_seleccion_mapa(this, juego) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);

    // Coloco la imagen con un Color Key para que el fondo sea transparente
    QPixmap pixmap(QString(ASSETS_PATH) + RUTA_IMG_MENU_MULTIPLAYER);
    QRgb colorKey = qRgb(R_MULTIPLAYER, G_MULTIPLAYER, B_MULTIPLAYER);
    QBitmap mask = pixmap.createMaskFromColor(colorKey, Qt::MaskInColor);
    pixmap.setMask(mask);

    label.setPixmap(pixmap.scaled(TAM_IMG_MULTIPLAYER, TAM_IMG_MULTIPLAYER, Qt::KeepAspectRatio));
    label.setGeometry(QRect(OFFSET_X_IMG_MULTIPLAYER_BTN + ANCHO_MULTIPLAYER_BTN,
                            OFFSET_Y_IMG_MULTIPLAYER_BTN, TAM_IMG_MULTIPLAYER,
                            TAM_IMG_MULTIPLAYER));

    connect(&multiplayer_btn, &QPushButton::clicked, this, &MenuCrearPartida::desplegar_popup);
}


void MenuCrearPartida::desplegar_popup() {
    popup_cant_jugadores.exec();
}


void MenuCrearPartida::crear_partida() {
    juego.definir_codigo_partida(popup_cant_jugadores.obtener_seleccion());
    menu_seleccion_mapa.move(this->pos());
    menu_seleccion_mapa.show();
    hide();
}
