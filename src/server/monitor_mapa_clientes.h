#ifndef MONITOR_MAPA_CLIENTES_H
#define MONITOR_MAPA_CLIENTES_H

#include <map>

#include "../common/queue.h"
#include "../common/snapshot_dto.h"

class MonitorMapaClientes {
private:
    std::mutex m;

    std::map<int, TipoPersonaje> mapa_clientes_juego;

public:
    void agregar_cliente(int id_cliente, TipoPersonaje personaje);

    int obtener_cantidad_clientes();

    std::map<int, TipoPersonaje> obtener_clientes();
};

#endif
