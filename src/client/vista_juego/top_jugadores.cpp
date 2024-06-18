#include "top_jugadores.h"

bool comparar_puntajes(const std::pair<int32_t, uint32_t>& a,
                       const std::pair<int32_t, uint32_t>& b) {
    return a.second < b.second;
}

TopJugadores::TopJugadores(): top_actualizado(false) {}

std::vector<std::pair<int32_t, uint32_t>> TopJugadores::obtener_top_jugadores(bool obtener_todos) {
    if (obtener_todos) {
        std::sort(jugadores.begin(), jugadores.end(), comparar_puntajes);
        return jugadores;
    }

    if (top_actualizado) {
        return top_jugadores;
    }

    top_jugadores.clear();
    for (const auto& jugador: jugadores) {
        top_jugadores.push_back(jugador);
        std::push_heap(top_jugadores.begin(), top_jugadores.end(), comparar_puntajes);
        if (top_jugadores.size() > CANTIDAD_TOP_JUGADORES) {
            std::pop_heap(top_jugadores.begin(), top_jugadores.end(), comparar_puntajes);
            top_jugadores.pop_back();
        }
    }
    std::sort(top_jugadores.begin(), top_jugadores.end(), comparar_puntajes);
    top_actualizado = true;
    return top_jugadores;
}

void TopJugadores::actualizar_jugadores(std::vector<std::pair<int32_t, uint32_t>>&& jugadores) {
    this->jugadores = std::move(jugadores);
}

TopJugadores::~TopJugadores() = default;
