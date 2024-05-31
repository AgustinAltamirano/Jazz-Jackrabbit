#include "snapshot_dto.h"

#include <iostream>

SnapshotDTO::SnapshotDTO(): clientes(), fin_juego(false) {}

SnapshotDTO::SnapshotDTO(const std::vector<ClienteDTO> clientes):
        clientes(clientes), fin_juego(false) {}

void SnapshotDTO::agregar_cliente(ClienteDTO cliente) { clientes.push_back(cliente); }

std::vector<ClienteDTO> SnapshotDTO::obtener_clientes() { return clientes; }

bool SnapshotDTO::es_fin_juego() const { return fin_juego; }

void SnapshotDTO::establecer_fin_juego(bool fin_juego) { this->fin_juego = fin_juego; }
