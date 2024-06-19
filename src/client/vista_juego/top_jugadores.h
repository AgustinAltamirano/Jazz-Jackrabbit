#ifndef TOP_JUGADORES_H
#define TOP_JUGADORES_H

#include <algorithm>
#include <cstdint>
#include <tuple>
#include <utility>
#include <vector>

#include "../../common/tipo_personaje.h"

#define CANTIDAD_TOP_JUGADORES 3

class TopJugadores {
private:
    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> jugadores;
    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> top_jugadores;

public:
    TopJugadores();

    TopJugadores(const TopJugadores&) = delete;
    TopJugadores& operator=(const TopJugadores&) = delete;

    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> obtener_top_jugadores(
            bool obtener_todos);

    void actualizar_jugadores(
            std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>>&& jugadores);

    ~TopJugadores();
};


#endif  // TOP_JUGADORES_H
