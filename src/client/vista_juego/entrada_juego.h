#ifndef ENTRADA_JUEGO_H
#define ENTRADA_JUEGO_H

#include <memory>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/queue.h"

#include "accion_juego_dto.h"

#define SALIR SDLK_ESCAPE

/** Clase encargada de leer la entrada del jugador y enviarla al hilo transmisor. */
class EntradaJuego {
private:
    static const std::unordered_map<SDL_Keycode, const AccionJuego> MAPA_ACCIONES;

    // Es una cola de AccionJuego provisoriamente
    Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones;

public:
    explicit EntradaJuego(Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones);

    EntradaJuego(const EntradaJuego&) = delete;

    EntradaJuego& operator=(const EntradaJuego&) = delete;

    /** Lee todos los eventos producidos por el jugador y envía la acción correspondiente. */
    bool procesar_entrada() const;
};


#endif  // ENTRADA_JUEGO_H
