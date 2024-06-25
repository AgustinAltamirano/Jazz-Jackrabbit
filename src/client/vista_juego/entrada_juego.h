#ifndef ENTRADA_JUEGO_H
#define ENTRADA_JUEGO_H

#include <unordered_map>
#include <unordered_set>

#include <SDL2pp/SDL2pp.hh>
#include <SDL_keycode.h>

#include "../juego/cliente.h"

#define SALIR SDLK_ESCAPE
#define MOSTRAR_TOP SDLK_TAB

/**
 * @class EntradaJuego
 * @brief Clase encargada de leer la entrada del jugador y enviarla al hilo transmisor. */
class EntradaJuego {
private:
    /** Mapa que indica la acción que debe realizarse al presionar ciertas teclas una sola vez. */
    static const std::unordered_map<SDL_Keycode, const TipoComando> MAPA_ACCIONES_PRESIONAR_TECLA;

    /** Mapa que indica la acción que debe realizarse al mantener presionada ciertas teclas. */
    static const std::unordered_map<SDL_Keycode, const TipoComando>
            MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA;

    /** Mapa que indica la acción que debe realizarse al soltar ciertas teclas. */
    static const std::unordered_map<SDL_Keycode, const TipoComando> MAPA_ACCIONES_SOLTAR_TECLA;

    /**
     * Set que indica las acciones que se deben seguir enviando mientras se mantenga presionada
     * una tecla.
     */
    std::unordered_set<TipoComando> acciones_continuas_a_enviar;

    Cliente& cliente;
    bool top_activo;

public:
    explicit EntradaJuego(Cliente& cliente);

    EntradaJuego(const EntradaJuego&) = delete;

    EntradaJuego& operator=(const EntradaJuego&) = delete;

    /** @brief Lee todos los eventos producidos por el jugador y envía la acción correspondiente. */
    [[nodiscard]] bool procesar_entrada();

    /** @brief Indica si se debe mostrar el top de jugadores o no. */
    [[nodiscard]] bool mostrar_top() const;

    ~EntradaJuego();
};


#endif  // ENTRADA_JUEGO_H
