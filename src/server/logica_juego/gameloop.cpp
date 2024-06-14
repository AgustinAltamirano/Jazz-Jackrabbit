#include "gameloop.h"

#include "../../common/comando_dto.h"
#include "../../common/constantes.h"
#include "../../common/snapshot_dto.h"

void hacer_tick(int tiempo) { std::this_thread::sleep_for(std::chrono::milliseconds(tiempo)); }

void Gameloop::stop() { this->keep_talking = false; }

Gameloop::Gameloop(const std::string& archivo_escenario,
                   const std::map<int32_t, TipoPersonaje>& mapa, Queue<ComandoDTO*>& cola_entrada,
                   std::map<int, Queue<std::shared_ptr<SnapshotDTO>>*>& colas_salida):
        keep_talking(true),
        is_alive(true),
        cola_entrada(cola_entrada),
        colas_salida(colas_salida),
        escenario(archivo_escenario) {
    const std::vector<spawnpoint> lugares_spawnpoints = escenario.get_spawns();
    uint32_t index_spawns = 0;
    for (auto& [id, tipo]: mapa) {
        const int32_t spawn_x = lugares_spawnpoints[index_spawns].pos_x;
        const int32_t spawn_y = lugares_spawnpoints[index_spawns].pos_y;
        personajes.emplace(id, personaje(id, tipo, spawn_x, spawn_y));
        ++index_spawns;
        if (index_spawns >= size(lugares_spawnpoints)) {
            index_spawns = 0;
        }
    }
}

void Gameloop::run() {
    // enviando dto escenario
    auto snapshot_escenario = escenario.crear_snapshot();
    for (auto& cola_salida: colas_salida) {
        cola_salida.second->try_push(snapshot_escenario);
    }

    while (this->keep_talking) {
        // comienzo el cronómetro
        auto tiempo_inicio = std::chrono::high_resolution_clock::now();

        // seccion1 se encarga de leer la cola de entrada y efectuar los movimientos en los
        // jugadores
        std::map<int32_t, std::vector<TipoComando>> acciones;
        ComandoDTO* comando;
        while (cola_entrada.try_pop(comando)) {
            // asumo que el dto ya puede implementar conseguir el id y la accion que trae
            acciones[comando->obtener_id_cliente()].push_back(comando->obtener_comando());
        }
        for (auto& entidad: personajes) {
            entidad.second.pasar_tick();
            entidad.second.efectuar_gravedad();
        }
        for (const auto& accion: acciones) {
            if (personajes.at(accion.first).ejecutar_accion(accion.second)) {
                escenario.jugador_dispara(accion.first, personajes.at(accion.first));
            }
        }

        // seccion2 chequea colisiones con el entorno y los cambios de estado de los personajes
        escenario.colisiones_bloques_rectos(personajes);
        // escenario.colisiones_bloques_angulo(personajes);
        escenario.chequear_caida_y_objetos(personajes);

        // seccion3 chequea colisiones con los puntos, municiones y enemigos
        escenario.manejar_balas(personajes);
        escenario.hacer_tick_enemigos();

        // enviar dto vuelta
        auto snapshot_juego = std::make_shared<SnapshotDTO>(escenario.get_escenario());
        for (const auto& entidad: personajes) {
            ClienteDTO jugador_dto = entidad.second.crear_dto();
            snapshot_juego->agregar_cliente(std::move(jugador_dto));
        }
        for (auto& cola_salida: colas_salida) {
            cola_salida.second->try_push(snapshot_juego);
        }

        // freno el cronometro y pongo a dormir por los milisegundos por frame menos la diferencia
        auto tiempo_final = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> tiempo_cpu = tiempo_final - tiempo_inicio;
        int tiempo_sleep = TIEMPO_FRAME - static_cast<int>(tiempo_cpu.count());
        if (tiempo_sleep > 0) {
            hacer_tick(tiempo_sleep);
        }
    }
    this->is_alive = false;
}
