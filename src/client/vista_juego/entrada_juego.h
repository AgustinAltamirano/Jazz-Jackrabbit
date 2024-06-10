#ifndef ENTRADA_JUEGO_H
#define ENTRADA_JUEGO_H

#include <memory>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/comando_dto.h"
#include "../../common/queue.h"
#include "../juego/cliente.h"

#define SALIR SDLK_ESCAPE

/** Clase encargada de leer la entrada del jugador y enviarla al hilo transmisor. */
class EntradaJuego {
private:
    static const std::unordered_map<SDL_Keycode, const TipoComando> MAPA_ACCIONES;

    Cliente& cliente;

public:
    explicit EntradaJuego(Cliente& cliente);

    EntradaJuego(const EntradaJuego&) = delete;

    EntradaJuego& operator=(const EntradaJuego&) = delete;

    /** Lee todos los eventos producidos por el jugador y envía la acción correspondiente. */
    [[nodiscard]] bool procesar_entrada() const;
};


#endif  // ENTRADA_JUEGO_H
