#include "gameloop.h"

#include "../../common/constantes.h"

void hacer_tick() { std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_FRAME)); }

void gameloop::kill() { this->keep_talking = false; }

gameloop::gameloop(const std::string& archivo_escenario, const std::map<int, TipoPersonaje>& mapa,
                   Queue<SnapshotDTO>& cola_entrada):
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

void gameloop::run() {}
