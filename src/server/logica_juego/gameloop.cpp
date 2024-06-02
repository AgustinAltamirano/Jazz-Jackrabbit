#include "gameloop.h"

#include "../../common/constantes.h"

void hacer_tick() { std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_FRAME)); }

void gameloop::kill() { this->keep_talking = false; }

gameloop::gameloop(const std::string& archivo_escenario,
                   const std::map<int32_t, TipoPersonaje>& mapa, Queue<SnapshotDTO>& cola_entrada):
        keep_talking(true),
        is_alive(true),
        cola_entrada(cola_entrada),
        escenario(archivo_escenario) {
    std::vector<spawnpoint> lugares_spawnpoints = escenario.get_spawns();
    uint32_t index_spawns = 0;
    for (auto& [id, tipo]: mapa) {
        const int32_t spawn_x = lugares_spawnpoints[index_spawns].pos_x;
        const int32_t spawn_y = lugares_spawnpoints[index_spawns].pos_y;
        personajes[id] = personaje(id, tipo, spawn_x, spawn_y);
        ++index_spawns;
        if (index_spawns >= size(lugares_spawnpoints)) {
            index_spawns = 0;
        }
    }
}

void gameloop::run() {
    // enviar dto escenario
    while (this->keep_talking) {

        // seccion1 se encarga de leer la cola de entrada y efectuar los movimientos en los
        // jugadores
        std::map<int32_t, std::vector<AccionJuego>> acciones;
        SnapshotDTO comando;
        while (cola_entrada.try_pop(comando)) {
            // asumo que el dto ya puede implementar conseguir el id y la accion que trae
            acciones[comando.id].emplace_back(comando.accion);
        }
        for (const auto& accion: acciones) {
            personajes[accion.first].cambiar_velocidad(accion.second);
        }

        // seccion2 chequea colisiones con el entorno y los cambios de estado de los personajes
        escenario.colisiones_bloques_rectos(personajes);
        escenario.colisiones_bloques_angulo(personajes);
        escenario.chequear_caida(personajes);

        // seccion3 chequea colisiones con los puntos, municiones y enemigos
        //  por hacer

        // enviar dto vuelta
        hacer_tick();  // por ahora es fijo
    }
    this->is_alive = false;
}
