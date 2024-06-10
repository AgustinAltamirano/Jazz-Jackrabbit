#ifndef CONSTANTES_H
#define CONSTANTES_H

// CONFIGURACION Y SUS CONSTANTES
#define ARCHIVO_CONFIG "../../configuracion.yaml"
#define MAX_JUG_POR_PARTIDA "max_jugadores_por_partida"
#define MAX_PARTIDAS "max_partidas"
#define VIDA_INICIAL "vida_inicial"
#define GRAVEDAD "aceleracion_gravedad"

#define VEL_ARMA_INF "velocidad_arma_infinita"
#define DANO_ARMA_INF "dano_arma_infinita"
#define FRAMES_REC_ARMA_INF "frames_recarga_arma_infinita"

#define VEL_ARMA1 "velocidad_arma1"
#define DANO_ARMA1 "dano_arma1"
#define FRAMES_REC_ARMA1 "frames_recarga_arma1"

#define VEL_ARMA2 "velocidad_arma2"
#define CAIDA_ARMA2 "caida_arma2"
#define DANO_ARMA2 "dano_arma2"
#define FRAMES_REC_ARMA2 "frames_recarga_arma2"

#define VEL_ARMA3 "velocidad_arma3"
#define DANO_ARMA3 "dano_arma3"
#define FRAMES_REC_ARMA3 "frames_recarga_arma3"

#define VIDA_LAGARTO "vida_lagarto"
#define VIDA_MURCIELAGO "vida_murcielago"
#define VIDA_ESQUELETO "vida_esqueleto"

#define DANO_LAGARTO "dano_lagarto"
#define DANO_MURCIELAGO "dano_murcielago"
#define DANO_ESQUELETO "dano_esqueleto"

#define VELOCIDAD_LAGARTO "velocidad_lagarto"
#define VELOCIDAD_MURCIELAGO "velocidad_murcielago"
#define VELOCIDAD_ESQUELETO "velocidad_esqueleto"

#define PUNTOS_LAGARTO "puntos_lagarto"
#define PUNTOS_MURCIELAGO "puntos_murcielago"
#define PUNTOS_ESQUELETO "puntos_esqueleto"

#define FRAMES_REVIVIR_LAG "frames_hasta_revivir_lagarto"
#define FRAMES_REVIVIR_MUR "frames_hasta_revivir_murcielago"
#define FRAMES_REVIVIR_ESQ "frames_hasta_revivir_esqueleto"

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

// para la lectura de mapas
#define TAMANO_BLOQUE 32

// para los enemigos
#define ALTURA_ENEMIGO 32
#define ANCHO_ENEMIGO 32

#endif  // CONSTANTES_H
