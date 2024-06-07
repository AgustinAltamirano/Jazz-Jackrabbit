#ifndef CONSTANTES_H
#define CONSTANTES_H


typedef enum {
    ESCENARIO_INDEFINIDO = 0,
    ESCENARIO1,
    ESCENARIO2,
} TipoEscenarioEditor;

typedef enum {
    PISO = 0,
    TECHO,
    PARED,
    DIAGONAL,
    DIAGONAL_INVERTIDO,
    SOPORTE_DIAGONAL,
    SOPORTE_DIAGONAL_INVERTIDO,
    SPAWNPOINT_JUGADOR,
    SPAWNPOINT_ENEMIGO,
    GEMA,
    MONEDA,
    TEXTURA
} TipoItemEditor;

Q_DECLARE_METATYPE(TipoEscenarioEditor)
Q_DECLARE_METATYPE(TipoItemEditor)

struct ItemEscena {
    TipoItemEditor tipo;
    TipoEscenarioEditor mapa_asociado;
    QPixmap imagen;
};

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480
#define TAM_ITEM 32
#define TITULO_VENTANA "Editor de mapas"
#define RUTA_ICONO "/editor/img/icono_editor.png"

#define RUTA_IMG_ITEMS "/editor/img/"
#define ITEMS_CONFIG "items.yaml"

#define RUTA_IMG_ESCENARIOS "/sprites/escenarios/"
#define ESCENARIOS_CONFIG "escenarios.yaml"
#define COORD_FONDO 0

#define MARGEN_ALTO 60
#define MARGEN_ANCHO 120
#define ALTO_MENU_BAR 30

#define KEY_POSICION_BTN "posicion"
#define KEY_TIPO_BTN "tipo"
#define KEY_MAPA_BTN "mapa_asociado"
#define KEY_TIPO_ITEM 0
#define KEY_MAPA_ASOCIADO 1

#define ALTO_LISTA_ITEMS 50

#endif  // CONSTANTES_H
