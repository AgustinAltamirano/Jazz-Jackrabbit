#include "snapshot_dto.h"

#include <iostream>

SnapshotDTO::SnapshotDTO(): clientes(), bloques_escenario(), tipo_escenario(), fin_juego(false) {}

SnapshotDTO::SnapshotDTO(TipoEscenario tipo_escenario):
        clientes(), bloques_escenario(), tipo_escenario(tipo_escenario), fin_juego(false) {}

SnapshotDTO::SnapshotDTO(std::vector<ClienteDTO> clientes, std::vector<BloqueEscenarioDTO> bloques,
                         TipoEscenario tipo_escenario):
        clientes(clientes),
        bloques_escenario(bloques),
        tipo_escenario(tipo_escenario),
        fin_juego(false) {}

void SnapshotDTO::establecer_tipo_escenario(TipoEscenario tipo_escenario) {
    this->tipo_escenario = tipo_escenario;
}

TipoEscenario SnapshotDTO::obtener_tipo_escenario() { return tipo_escenario; }

void SnapshotDTO::agregar_cliente(ClienteDTO cliente) { clientes.push_back(cliente); }

std::vector<ClienteDTO> SnapshotDTO::obtener_clientes() { return clientes; }

void SnapshotDTO::agregar_bloque_escenario(BloqueEscenarioDTO bloque_escenario) {
    bloques_escenario.push_back(bloque_escenario);
}

std::vector<BloqueEscenarioDTO> SnapshotDTO::obtener_bloques_escenario() {
    return bloques_escenario;
}

bool SnapshotDTO::es_fin_juego() { return fin_juego; }

void SnapshotDTO::establecer_fin_juego(bool fin_juego) { this->fin_juego = fin_juego; }
