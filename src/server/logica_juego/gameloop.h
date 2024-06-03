#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <atomic>
#include <chrono>
#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../common/queue.h"
#include "../../common/snapshot_dto.h"
#include "../../common/thread.h"
#include "assets/spawnpoint.h"

#include "manejadorEscenario.h"
#include "personaje.h"

class gameloop: public Thread {
private:
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

    Queue<SnapshotDTO>& cola_entrada;
    // Monitor de salida de datos

    // aca todos los controladores
    std::map<int32_t, personaje> personajes;
    manejadorEscenario escenario;
    // controlador enemigos, etc

public:
    void run() override;
    /*CONSTRUCTOR VA A NECESITAR
     *Puntero a cola de entrada (o un monitor a ella)
     *Puntero al monitor de colas de salida
     *nombre del archivo que contiene el escenario
     *un mapa con los ids de personajes que se crearan apuntando al tipo de personaje
     */
    explicit gameloop(const std::string& archivo_escenario,
                      const std::map<int32_t, TipoPersonaje>& mapa,
                      Queue<SnapshotDTO>& cola_entrada);
    void kill() override;
};

#endif
