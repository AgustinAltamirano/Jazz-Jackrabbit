#include "entrada_juego.h"

#include <SDL_events.h>
#include <SDL_keycode.h>

const std::unordered_map<SDL_Keycode, const TipoComando>
        EntradaJuego::MAPA_ACCIONES_PRESIONAR_TECLA{{SDLK_w, SALTAR},
                                                    {SDLK_SPACE, DISPARAR_ACCION},
                                                    {SDLK_q, ARMA_ANTERIOR},
                                                    {SDLK_e, ARMA_SIGUIENTE},
                                                    {SDLK_h, ACTIVAR_ATAQUE_ESPECIAL},
                                                    {SDLK_i, TRUCO1},
                                                    {SDLK_o, TRUCO2},
                                                    {SDLK_p, TRUCO3}};

const std::unordered_map<SDL_Keycode, const TipoComando>
        EntradaJuego::MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA{
                {SDLK_a, MOVER_IZQ}, {SDLK_d, MOVER_DER}, {SDLK_g, ACTIVAR_DASH}};

const std::unordered_map<SDL_Keycode, const TipoComando> EntradaJuego::MAPA_ACCIONES_SOLTAR_TECLA{
        {SDLK_a, PARAR_MOVER_IZQ}, {SDLK_d, PARAR_MOVER_DER}, {SDLK_g, DESACTIVAR_DASH}};

EntradaJuego::EntradaJuego(Cliente& cliente): cliente(cliente), top_activo(false) {}

bool EntradaJuego::procesar_entrada() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT ||
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SALIR)) {
            return false;
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == MOSTRAR_TOP) {
            top_activo = true;
        }

        if (event.type == SDL_KEYUP && event.key.keysym.sym == MOSTRAR_TOP) {
            top_activo = false;
        }

        if (event.type == SDL_KEYDOWN &&
            MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA.count(event.key.keysym.sym)) {
            acciones_continuas_a_enviar.insert(
                    MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA.at(event.key.keysym.sym));
        }

        if (event.type == SDL_KEYUP &&
            MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA.count(event.key.keysym.sym)) {
            if (acciones_continuas_a_enviar.count(
                        MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA.at(event.key.keysym.sym))) {
                acciones_continuas_a_enviar.erase(
                        MAPA_ACCIONES_MANTENER_PRESIONADA_TECLA.at(event.key.keysym.sym));
            }
            cliente.realizar_accion(MAPA_ACCIONES_SOLTAR_TECLA.at(event.key.keysym.sym));
        }

        if (event.type == SDL_KEYDOWN &&
            MAPA_ACCIONES_PRESIONAR_TECLA.count(event.key.keysym.sym)) {
            cliente.realizar_accion(MAPA_ACCIONES_PRESIONAR_TECLA.at(event.key.keysym.sym));
        }
    }

    for (const auto& accion: acciones_continuas_a_enviar) {
        cliente.realizar_accion(accion);
    }

    return true;
}

bool EntradaJuego::mostrar_top() const { return top_activo; }

EntradaJuego::~EntradaJuego() = default;
