#ifndef ENTRADA_JUEGO_H
#define ENTRADA_JUEGO_H

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/queue.h"

// Provisorio (esto tendría que definirse en el protocolo)
typedef enum {
    SALTAR = 0,
    MOVER_IZQ,
    MOVER_DER,
    ACTIVAR_DASH,
    DISPARAR_ACCION,
    ARMA_ANTERIOR,
    ARMA_SIGUIENTE,
} AccionJuego;

#define SALIR SDLK_ESCAPE

/** Clase encargada de leer la entrada del jugador y enviarla al hilo transmisor. */
class EntradaJuego {
private:
    static const std::unordered_map<SDL_Keycode, const AccionJuego> MAPA_ACCIONES;

    // Es una cola de AccionJuego provisoriamente
    Queue<int>& cola_acciones;

public:
    explicit EntradaJuego(Queue<int>& cola_acciones);

    EntradaJuego(const EntradaJuego&) = delete;

    EntradaJuego& operator=(const EntradaJuego&) = delete;

    /** Lee todos los eventos producidos por el jugador y envía la acción correspondiente. */
    void procesar_entrada() const;
};


#endif  // ENTRADA_JUEGO_H
