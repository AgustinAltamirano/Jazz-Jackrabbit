#ifndef CONSTANTES_H
#define CONSTANTES_H

// CONFIGURACION Y SUS CONSTANTES
#define ARCHIVO_CONFIG "../../configuracion.yml"
#define MAX_JUG_POR_PARTIDA "max_jugadores_por_partida"
#define MAX_PARTIDAS "max_partidas"
#define VIDA_INICIAL "vida_inicial"
#define GRAVEDAD "aceleracion_gravedad"

// CONFIGURACION PERSONAJE
#define ANCHO_INICIAL 40
#define ALTO_INICIAL 50

// GAMELOOP
#define TIEMPO_FRAME 33
// 33 milisegundos equivale a 30 fps
// se se quiere 60 fps cambiar a 17 milisegundos
#define FRAMES_POR_SEGUNDO 30

// objetos recogibles
#define PUNTOS_GEMA 2500
#define PUNTOS_MONEDA 500
#define MUNICIONES_ARMA1 25
#define MUNICIONES_ARMA2 10
#define MUNICIONES_ARMA3 5
#define VIDA_COMIDA 1

#endif  // CONSTANTES_H
