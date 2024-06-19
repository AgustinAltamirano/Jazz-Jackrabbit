#ifndef ENTRADA_JUEGO_H
#define ENTRADA_JUEGO_H

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../juego/cliente.h"

#define SALIR SDLK_ESCAPE
#define MOSTRAR_TOP SDLK_TAB

/** Clase encargada de leer la entrada del jugador y enviarla al hilo transmisor. */
class EntradaJuego {
private:
    static const std::unordered_map<SDL_Keycode, const TipoComando> MAPA_ACCIONES_PRESIONAR_TECLA;

    static const std::unordered_map<SDL_Keycode, const TipoComando> MAPA_ACCIONES_SOLTAR_TECLA;

    Cliente& cliente;
    bool top_activo;

public:
    explicit EntradaJuego(Cliente& cliente);

    EntradaJuego(const EntradaJuego&) = delete;

    EntradaJuego& operator=(const EntradaJuego&) = delete;

    /** Lee todos los eventos producidos por el jugador y envía la acción correspondiente. */
    [[nodiscard]] bool procesar_entrada();

    [[nodiscard]] bool mostrar_top() const;

    ~EntradaJuego();
};


#endif  // ENTRADA_JUEGO_H
