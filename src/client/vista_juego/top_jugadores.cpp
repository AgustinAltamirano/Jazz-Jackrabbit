#include "top_jugadores.h"

bool comparar_puntajes(const std::tuple<int32_t, uint32_t, TipoPersonaje>& a,
                       const std::tuple<int32_t, uint32_t, TipoPersonaje>& b) {
    return std::get<1>(a) > std::get<1>(b);
}

bool comparar_puntajes_heap(const std::tuple<int32_t, uint32_t, TipoPersonaje>& a,
                            const std::tuple<int32_t, uint32_t, TipoPersonaje>& b) {
    return std::get<1>(a) < std::get<1>(b);
}

TopJugadores::TopJugadores() {}

std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> TopJugadores::obtener_top_jugadores(
        const bool obtener_todos) {
    if (obtener_todos) {
        std::sort(jugadores.begin(), jugadores.end(), comparar_puntajes);
        return jugadores;
    }

    top_jugadores.clear();
    for (const auto& jugador: jugadores) {
        top_jugadores.push_back(jugador);
        std::push_heap(top_jugadores.begin(), top_jugadores.end(), comparar_puntajes_heap);
        if (top_jugadores.size() > CANTIDAD_TOP_JUGADORES) {
            std::pop_heap(top_jugadores.begin(), top_jugadores.end(), comparar_puntajes_heap);
            top_jugadores.pop_back();
        }
    }
    std::sort(top_jugadores.begin(), top_jugadores.end(), comparar_puntajes);
    return top_jugadores;
}

void TopJugadores::actualizar_jugadores(
        std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>>&& jugadores) {
    this->jugadores = std::move(jugadores);
}

TopJugadores::~TopJugadores() = default;
