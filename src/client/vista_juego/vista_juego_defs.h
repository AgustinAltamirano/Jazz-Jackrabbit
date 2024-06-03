#ifndef VISTA_JUEGO_DEFS_H
#define VISTA_JUEGO_DEFS_H

#define MILISEGUNDOS_POR_FRAME 33

#define MILISEGUNDOS_POR_SPRITE 80

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

/**
 * Rutas usadas para cargar los sprites y las coordenadas de cada uno en sus respectivas imágenes.
 */
#define RUTA_SPRITES "/sprites"
#define DIR_PERSONAJES "/personajes/"
#define PERSONAJES_CONFIG "/personajes.yaml"

#define DIR_ESCENARIOS "/escenarios/"
#define ESCENARIOS_CONFIG "/escenarios.yaml"

#define COLOR_KEY_PERSONAJES_RED 44
#define COLOR_KEY_PERSONAJES_GREEN 102
#define COLOR_KEY_PERSONAJES_BLUE 150

#define COLOR_KEY_PERSONAJES                                                \
    ((COLOR_KEY_PERSONAJES_RED << 24) + (COLOR_KEY_PERSONAJES_BLUE << 16) + \
     (COLOR_KEY_PERSONAJES_GREEN << 8) + COLOR_KEY_PERSONAJES_RED)

#define COLOR_KEY_ESCENARIOS_RED 87
#define COLOR_KEY_ESCENARIOS_GREEN 0
#define COLOR_KEY_ESCENARIOS_BLUE 203

#define COLOR_KEY_ESCENARIOS                                                \
    ((COLOR_KEY_ESCENARIOS_RED << 24) + (COLOR_KEY_ESCENARIOS_BLUE << 16) + \
     (COLOR_KEY_ESCENARIOS_GREEN << 8) + COLOR_KEY_ESCENARIOS_RED)

#endif  // VISTA_JUEGO_DEFS_H
