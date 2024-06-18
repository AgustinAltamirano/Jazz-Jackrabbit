#ifndef TOP_JUGADORES_H
#define TOP_JUGADORES_H

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

#define CANTIDAD_TOP_JUGADORES 3

class TopJugadores {
private:
    std::vector<std::pair<int32_t, uint32_t>> jugadores;
    std::vector<std::pair<int32_t, uint32_t>> top_jugadores;
    bool top_actualizado;

public:
    TopJugadores();

    TopJugadores(const TopJugadores&) = delete;
    TopJugadores& operator=(const TopJugadores&) = delete;

    std::vector<std::pair<int32_t, uint32_t>> obtener_top_jugadores(bool obtener_todos);

    void actualizar_jugadores(std::vector<std::pair<int32_t, uint32_t>>&& jugadores);

    ~TopJugadores();
};


#endif  // TOP_JUGADORES_H
