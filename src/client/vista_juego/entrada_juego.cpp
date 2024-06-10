#include "entrada_juego.h"

const std::unordered_map<SDL_Keycode, const TipoComando> EntradaJuego::MAPA_ACCIONES{
        {SDLK_w, SALTAR},        {SDLK_a, MOVER_IZQ},           {SDLK_d, MOVER_DER},
        {SDLK_x, ACTIVAR_DASH},  {SDLK_SPACE, DISPARAR_ACCION}, {SDLK_q, ARMA_ANTERIOR},
        {SDLK_e, ARMA_SIGUIENTE}};

EntradaJuego::EntradaJuego(Cliente& cliente): cliente(cliente) {}

bool EntradaJuego::procesar_entrada() const {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT ||
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SALIR)) {
            return false;
        }
        if (event.type != SDL_KEYDOWN || !MAPA_ACCIONES.count(event.key.keysym.sym)) {
            continue;
        }

        cliente.realizar_accion(MAPA_ACCIONES.at(event.key.keysym.sym));
    }
    return true;
}
