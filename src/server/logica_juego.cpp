#include "logica_juego.h"

#include <vector>

LogicaJuego::LogicaJuego() {}

void LogicaJuego::agregar_cliente(const int32_t& id_cliente, const TipoPersonaje& personaje) {
    ClienteJuego* cliente = new ClienteJuego(id_cliente, personaje);
    mapa_clientes_juego[id_cliente] = cliente;
}

SnapshotDTO LogicaJuego::obtener_snapshot() {
    SnapshotDTO snapshot_dto;
    for (const auto& c: mapa_clientes_juego) {
        ClienteJuego* cliente_juego = c.second;
        ClienteDTO cliente_dto(cliente_juego->obtener_id(), cliente_juego->obtener_personaje());
        snapshot_dto.agregar_cliente(cliente_dto);
    }
    return snapshot_dto;
}

LogicaJuego::~LogicaJuego() {}
