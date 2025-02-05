#ifndef CONSTANTES_MENU_H
#define CONSTANTES_MENU_H

#include "../../common/tipo_personaje.h"
#include "../../common/tipo_escenario.h"

enum PosicionBoton {
    POS_NEWGAME_BTN,
    POS_JOINGAME_BTN,
};

Q_DECLARE_METATYPE(TipoPersonaje)
Q_DECLARE_METATYPE(TipoEscenario)

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480
#define CANT_EFECTOS_SONIDO 6
#define TITULO_VENTANAS "Jazz Jackrabbit 2"
#define RUTA_ICONO "/menu/img/icono_menu.png"

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

#define RUTA_EFECTOS_SONIDO "/menu/sfx/select"
#define EXTENSION_EFECTOS_SONIDO ".wav"
#define VOLUMEN_EFECTOS_SONIDO 10
#define VOLUMEN_MUSICA 40
#define RUTA_MUSICA_FONDO "/menu/sfx/musica_menu.mp3"

#define RUTA_FUENTE "/menu/img/Jazz-Jackrabbit-2.ttf"
#define TAMANIO_FUENTE 24
#define TAMANIO_FUENTE_BTN 40

#define RUTA_IMG_INICIAL "/menu/img/bgd_mainmenu.jpg"
#define RUTA_IMG_MENU "/menu/img/bgd_menuinicial.png"
#define RUTA_IMG_MENU_MULTIPLAYER "/menu/img/multiplayer.png"

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

#define ANCHO_SEL_PLAYER 180
#define ALTO_SEL_PLAYER 180
#define ANCHO_BTN_MAPA 150
#define ALTO_BTN_MAPA 80
#define ANCHO_IMG_MAPA 306
#define ALTO_IMG_MAPA 356
#define ANCHO_SEL_NAME 140
#define ALTO_SEL_NAME 50

#define ANCHO_POPUP 215
#define ALTO_POPUP 95
#define LEFT_M_LABEL_POPUP 10
#define TOP_M_FILA_POPUP 10
#define ALTO_FILA_POPUP 31
#define LEFT_M_BTN_POPUP 20
#define TOP_M_BTN_POPUP 60
#define ANCHO_BTN_POPUP 166
#define ALTO_BTN_POPUP 25
#define ANCHO_SPINBOX_POPUP 61
#define LEFT_M_SPINBOX_POPUP 150
#define ANCHO_LABEL_POPUP 121
#define RUTA_CONFIG_YAML "/configuracion.yaml"

#define TITULO_POPUP_PARTIDA "Ingresar código"
#define CANT_MIN_PARTIDAS 1
#define TEXTO_LABEL_PARTIDAS "Código de partida:"
#define MAX_PARTIDAS_YAML "max_partidas"

#define MAX_JUG_YAML "max_jugadores_por_partida"
#define TITULO_POPUP_JUG "Ingresar cantidad"
#define CANT_MIN_JUG 2
#define TEXTO_LABEL_JUG "Jugadores:"

#define COD_PARTIDA_INCORRECTA (-1)

#endif  // CONSTANTES_MENU_H
