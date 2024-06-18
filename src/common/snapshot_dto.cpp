#include "snapshot_dto.h"

#include <utility>

SnapshotDTO::SnapshotDTO():
        tipo_escenario(), bloques_escenario(), clientes(), fin_juego(false), tiempo_restante(0) {}

SnapshotDTO::SnapshotDTO(const TipoEscenario tipo_escenario):
        tipo_escenario(tipo_escenario),
        bloques_escenario(),
        clientes(),
        fin_juego(false),
        tiempo_restante(0) {}

SnapshotDTO::SnapshotDTO(std::vector<ClienteDTO> clientes, std::vector<BloqueEscenarioDTO> bloques,
                         const TipoEscenario tipo_escenario):
        tipo_escenario(tipo_escenario),
        bloques_escenario(std::move(bloques)),
        clientes(std::move(clientes)),
        fin_juego(false),
        tiempo_restante(0) {}

void SnapshotDTO::establecer_tipo_escenario(TipoEscenario tipo_escenario) {
    this->tipo_escenario = tipo_escenario;
}

TipoEscenario SnapshotDTO::obtener_tipo_escenario() const { return tipo_escenario; }

void SnapshotDTO::agregar_cliente(ClienteDTO cliente) { clientes.push_back(cliente); }

void SnapshotDTO::agregar_bala(BalaDTO bala) { balas.push_back(bala); }

std::vector<BalaDTO>& SnapshotDTO::obtener_balas() { return balas; }

void SnapshotDTO::agregar_enemigo(EnemigoDTO enemigo) { enemigos.push_back(enemigo); }

std::vector<EnemigoDTO>& SnapshotDTO::obtener_enemigos() { return enemigos; }

void SnapshotDTO::agregar_recogible(RecogibleDTO recogible) { recogibles.push_back(recogible); }

std::vector<RecogibleDTO>& SnapshotDTO::obtener_recogibles() { return recogibles; }

std::vector<ClienteDTO>& SnapshotDTO::obtener_clientes() { return clientes; }

void SnapshotDTO::agregar_bloque_escenario(BloqueEscenarioDTO bloque_escenario) {
    bloques_escenario.push_back(bloque_escenario);
}

std::vector<BloqueEscenarioDTO>& SnapshotDTO::obtener_bloques_escenario() {
    return bloques_escenario;
}

bool SnapshotDTO::es_fin_juego() const { return fin_juego; }

void SnapshotDTO::establecer_fin_juego(const bool fin_juego) { this->fin_juego = fin_juego; }

void SnapshotDTO::agregar_tiempo_restante(int tiempo) { this->tiempo_restante = tiempo; }

int SnapshotDTO::obtener_tiempo_restante() const { return this->tiempo_restante; }
