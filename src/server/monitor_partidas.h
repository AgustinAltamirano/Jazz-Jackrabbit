#ifndef MONITOR_JUEGOS_H
#define MONITOR_JUEGOS_H

#include <list>

#include "partida.h"

class MonitorPartidas {
private:
    std::mutex m;
    std::list<Partida*> lista_partidas;

public:
    void agregar_nueva_partida(Partida* partida);

    int obtener_cantidad_partidas();

    Partida* obtener_partidas_por_codigo(const int32_t& codigo_partida);

    void join_partidas();

    bool borrar_cliente(int32_t& id_cliente);

    void eliminar_partidas_finalizadas();
};

#endif
