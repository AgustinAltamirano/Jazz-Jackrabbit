#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <atomic>
#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "../../common/queue.h"
#include "../../common/thread.h"

#include "personaje.h"

class gameloop: public Thread {
private:
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;
    std::map<int, personaje> personajes;
    // Queue<DOT>& cola_entrada;
    // Monitor de salida de datos

    // aca todos los controladores
    // controlador jugadores
    // controlador escenario
    // controlador enemigos, etc

public:
    void run() override;
    /*CONSTRUCTOR VA A NECESITAR
     *Puntero a cola de entrada (o un monitor a ella)
     *Puntero al monitor de colas de salida
     *nombre del archivo que contiene el escenario
     *un mapa con los ids de personajes que se crearan apuntando al tipo de personaje
     */
    explicit gameloop(std::string archivo_escenario, std::map<int, int>);
    void kill() override;
};

#endif
