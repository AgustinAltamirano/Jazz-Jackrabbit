#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <atomic>
#include <chrono>
#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../common/comando_dto.h"
#include "../../common/queue.h"
#include "../../common/snapshot_dto.h"
#include "../../common/thread.h"
#include "../../common/tipo_personaje.h"
#include "assets/spawnpoint.h"

#include "manejadorEscenario.h"
#include "personaje.h"

class Gameloop: public Thread {
private:
    std::atomic<bool>& keep_talking;
    std::atomic<bool> is_alive;

    Queue<ComandoDTO*>& cola_entrada;
    // como los jugadores no pueden conectarse en medio de una partida,
    // no hay rc si gameloop tiene acceso a las colas de salida
    std::map<int, Queue<std::shared_ptr<SnapshotDTO>>*> colas_salida;

    // aca todos los controladores
    std::map<int32_t, personaje> personajes;
    manejadorEscenario escenario;

public:
    void run() override;
    /*CONSTRUCTOR VA A NECESITAR
     *Puntero a cola de entrada (o un monitor a ella)
     *Puntero al monitor de colas de salida
     *nombre del archivo que contiene el escenario
     *un mapa con los ids de personajes que se crearan apuntando al tipo de personaje
     */
    explicit Gameloop(const std::string& archivo_escenario,
                      const std::map<int32_t, TipoPersonaje>& mapa,
                      Queue<ComandoDTO*>& cola_entrada,
                      std::map<int, Queue<std::shared_ptr<SnapshotDTO>>*>& colas_salida,
                      std::atomic<bool>& sigo_jugando);
    void stop() override;
};

#endif
