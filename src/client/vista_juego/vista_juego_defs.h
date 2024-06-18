#ifndef VISTA_JUEGO_DEFS_H
#define VISTA_JUEGO_DEFS_H

#define MILISEGUNDOS_POR_FRAME 33

#define ITERACIONES_POR_SPRITE 3

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

/** Son renderizados aquellos objetos visuales que tengan al menos parte de su sprite con:
 * -MARGEN_RENDERIZADO <= x <= ANCHO_VENTANA + MARGEN_RENDERIZADO
 * -MARGEN_RENDERIZADO <= y <= ALTO_VENTANA + MARGEN_RENDERIZADO
 */
#define MARGEN_RENDERIZADO 50

/** Posición en pantalla donde se muestra la cámara */
#define RENDER_CAMARA_X (ANCHO_VENTANA / 2)
#define RENDER_CAMARA_Y (ALTO_VENTANA * 3 / 4)


#define COLOR_PANTALLA_CARGA_RED 122
#define COLOR_PANTALLA_CARGA_GREEN 69
#define COLOR_PANTALLA_CARGA_BLUE 255

/**
 * Rutas usadas para cargar los sprites y las coordenadas de cada uno en sus respectivas imágenes.
 */
#define RUTA_SPRITES "/sprites"
#define DIR_PERSONAJES "/personajes/"
#define PERSONAJES_CONFIG "/personajes.yaml"

#define DIR_ESCENARIOS "/escenarios/"
#define ESCENARIOS_CONFIG "/escenarios.yaml"

#define DIR_ENEMIGOS "/enemigos/"
#define ENEMIGOS_CONFIG "/enemigos.yaml"

#define DIR_FUENTE "/fuente/"
#define FUENTE_CONFIG "/fuente.yaml"

#define DIR_ITEMS "/items/"
#define ITEMS_CONFIG "/items.yaml"

#define COLOR_KEY_PERSONAJES_RED 44
#define COLOR_KEY_PERSONAJES_GREEN 102
#define COLOR_KEY_PERSONAJES_BLUE 150

#define COLOR_KEY_ESCENARIOS_RED 87
#define COLOR_KEY_ESCENARIOS_GREEN 0
#define COLOR_KEY_ESCENARIOS_BLUE 203

#define COLOR_KEY_ENEMIGOS_RED 0
#define COLOR_KEY_ENEMIGOS_GREEN 128
#define COLOR_KEY_ENEMIGOS_BLUE 255


/** Constantes del HUD de cliente */

#define SEPARACION_ENTRE_NUMEROS 5

#define POS_PUNTOS_X 10
#define POS_PUNTOS_Y 10

#define POS_VIDA_X (ANCHO_VENTANA / 2)
#define POS_VIDA_Y 10

#define POS_ARMA_ACTUAL_X 10
#define POS_ARMA_ACTUAL_Y (ALTO_VENTANA - 30)

// Posición de la esquina superior derecha del id de jugador en el HUD
#define POS_ID_JUGADOR_X (ANCHO_VENTANA - 10)
#define POS_ID_JUGADOR_Y 10


#endif  // VISTA_JUEGO_DEFS_H
