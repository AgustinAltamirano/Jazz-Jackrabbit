#include "entrada_juego.h"

const std::unordered_map<SDL_Keycode, const TipoComando> EntradaJuego::MAPA_ACCIONES{
        {SDLK_w, SALTAR},
        {SDLK_a, MOVER_IZQ},
        {SDLK_d, MOVER_DER},
        {SDLK_x, ACTIVAR_DASH},
        {SDLK_SPACE, DISPARAR_ACCION},
        {SDLK_q, ARMA_ANTERIOR},
        {SDLK_e, ARMA_SIGUIENTE},
        {SDLK_i, TRUCO1},
        {SDLK_o, TRUCO2},
        {SDLK_p, TRUCO3}};

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

        if (event.type != SDL_KEYDOWN || !MAPA_ACCIONES.count(event.key.keysym.sym)) {
            continue;
        }

        cliente.realizar_accion(MAPA_ACCIONES.at(event.key.keysym.sym));
    }
    return true;
}

bool EntradaJuego::mostrar_top() const { return top_activo; }

EntradaJuego::~EntradaJuego() = default;
