#ifndef TOP_JUGADORES_H
#define TOP_JUGADORES_H

#include <algorithm>
#include <cstdint>
#include <tuple>
#include <utility>
#include <vector>

#include "../../common/tipo_personaje.h"

#define CANTIDAD_TOP_JUGADORES 3

/**
 * @class TopJugadores
 * @brief Clase auxiliar de @code HUD@endcode, utilizada para almacenar y obtener el top de
 * jugadores de la partida.
 */
class TopJugadores {
private:
    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> jugadores;
    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> top_jugadores;

public:
    TopJugadores();

    TopJugadores(const TopJugadores&) = delete;
    TopJugadores& operator=(const TopJugadores&) = delete;

    /**
     * @brief Obtiene el top de jugadores de la partida.
     * @param obtener_todos Indica si se deben obtener todos los jugadores o solo los del top 3.
     * @return Vector con los datos de los jugadores (id, puntos y tipo), ordenados de forma
     * descendente según la cantidad de puntos.
     */
    std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>> obtener_top_jugadores(
            bool obtener_todos);

    /**
     * @brief Actualiza la lista de jugadores de la partida.
     * @param jugadores Vector con los datos de los jugadores (id, puntos y tipo) de la partida.
     */
    void actualizar_jugadores(
            std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>>&& jugadores);

    ~TopJugadores();
};


#endif  // TOP_JUGADORES_H
