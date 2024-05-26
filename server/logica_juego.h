#ifndef LOGICA_JUEGO_H
#define LOGICA_JUEGO_H

#include "../common/snapshot_dto.h"
#include "../common/comando_dto.h"
#include "../game_logic/cliente_juego.h"
#include <map>
#include <utility>

class LogicaJuego {
private:
    std::map<int, ClienteJuego *> mapa_clientes_juego;

public:
    LogicaJuego();

    void agregar_cliente(const int32_t &id_cliente);

    SnapshotDTO obtener_snapshot();

    ~LogicaJuego();
};

#endif
