#ifndef CONSTANTES_MENU_H
#define CONSTANTES_MENU_H

enum PosicionBoton {
    POS_NEWGAME_BTN,
    POS_JOINGAME_BTN,
};

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480
#define CANT_EFECTOS_SONIDO 6

#define ALTURA_BTN 51
#define TOP_MARGIN_BTN 160
#define OFFSET_Y_BTN 100

#define ANCHO_NEWGAME_BTN 290
#define ALTO_NEWGAME_BTN ALTURA_BTN
#define OFFSET_X_NEWGAME_BTN ((ANCHO_PANTALLA - ANCHO_NEWGAME_BTN) / 2)
#define OFFSET_Y_NEWGAME_BTN (TOP_MARGIN_BTN + OFFSET_Y_BTN * POS_NEWGAME_BTN)
#define TEXTO_NEWGAME_BTN "NEW GAME"

#define ANCHO_JOINGAME_BTN 321
#define ALTO_JOINGAME_BTN ALTURA_BTN
#define OFFSET_X_JOINGAME_BTN ((ANCHO_PANTALLA - ANCHO_JOINGAME_BTN) / 2)
#define OFFSET_Y_JOINGAME_BTN (TOP_MARGIN_BTN + OFFSET_Y_BTN * POS_JOINGAME_BTN)
#define TEXTO_JOINGAME_BTN "JOIN GAME"

#define ANCHO_MULTIPLAYER_BTN 400
#define ALTO_MULTIPLAYER_BTN ALTURA_BTN
#define OFFSET_X_MULTIPLAYER_BTN 20
#define OFFSET_Y_MULTIPLAYER_BTN 215
#define TEXTO_MULTIPLAYER_BTN "MULTIPLAYER"

#define RUTA_EFECTOS_SONIDO "qrc:/sfx/sfx/select"
#define EXTENSION_EFECTOS_SONIDO ".wav"
#define VOLUMEN_EFECTOS_SONIDO 20
#define RUTA_MUSICA_FONDO "qrc:/sfx/sfx/Jazz Jackrabbit 2 Music - Menu.mp3"

#define RUTA_FUENTE ":/img/img/Jazz-Jackrabbit-2.ttf"
#define TAMANIO_FUENTE 24
#define TAMANIO_FUENTE_BTN 40

#define RUTA_IMG_INICIAL ":/img/img/bgd_mainmenu.jpg"
#define RUTA_IMG_MENU ":/img/img/bgd_menuinicial.png"
#define RUTA_IMG_MENU_MULTIPLAYER ":/img/img/multiplayer.png"

#define TEXTO_INICIO_BTN "Press click"

#define OFFSET_X_IMG_MULTIPLAYER_BTN 30
#define OFFSET_Y_IMG_MULTIPLAYER_BTN 150
#define TAM_IMG_MULTIPLAYER 180

// Defino los colores en RGB
#define R_MULTIPLAYER 0
#define G_MULTIPLAYER 128
#define B_MULTIPLAYER 255
#define RGB_BTN "rgb(255, 250, 11)"
#define RGB_HOVER_BTN "rgb(32, 182, 57)"

#endif  // CONSTANTES_MENU_H
