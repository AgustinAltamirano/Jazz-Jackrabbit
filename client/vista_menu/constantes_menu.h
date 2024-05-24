#ifndef CONSTANTES_MENU_H
#define CONSTANTES_MENU_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QFontDatabase>


#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480


#define ALTURA_BTN 51
#define LEFT_MARGIN_BTN 160
#define OFFSET_BTN 100


enum PosicionBoton {
    POS_NEWGAME_BTN,
    POS_JOINGAME_BTN,
};

#define WIDTH_NEWGAME_BTN 290
#define TEXT_NEWGAME_BTN "NEW GAME"
#define WIDTH_JOINGAME_BTN 321
#define TEXT_JOINGAME_BTN "JOIN GAME"


#define POS_MULTIPLAYER_BTN 0
#define WIDTH_MULTIPLAYER_BTN 400
#define TEXT_MULTIPLAYER_BTN "MULTIPLAYER"

#endif  // CONSTANTES_MENU_H
