#include "juego.h"

#include <chrono>
#include <cmath>
#include <optional>
#include <set>
#include <sstream>
#include <thread>
#include <utility>
#include <vector>

Juego::Juego(int id_cliente, Socket& socket):
        id_cliente(id_cliente), cliente(std::move(socket)), frecuencia(0.04) {}

Juego::~Juego() { this->cliente.join(); }

void Juego::start() {
    bool jugando = true;
    SnapshotDTO snapshot_dto;

    while (jugando) {
        auto t_inicio = std::chrono::high_resolution_clock::now();
        std::optional<SnapshotDTO> snapshot_optional = this->cliente.obtener_snapshot();
        if (snapshot_optional.has_value())
            snapshot_dto = snapshot_optional.value();

        if (snapshot_optional.has_value() && not snapshot_dto.es_fin_juego()) {
            this->ejecutar_ciclo_principal_juego(snapshot_dto);
        }

        jugando = !snapshot_dto.es_fin_juego();

        auto t_fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracion = t_fin - t_inicio;
        double descanso = this->frecuencia - duracion.count();
        if (descanso < 0) {
            double adelanto = -descanso;
            double perdida = adelanto - std::fmod(adelanto, this->frecuencia);
            t_inicio += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
                    std::chrono::duration<double>(perdida));
        } else {
            std::this_thread::sleep_for(std::chrono::duration<double>(descanso));
        }
    }
}

void Juego::ejecutar_ciclo_principal_juego(SnapshotDTO& snapshot_dto) {
    std::vector<ClienteDTO> clientes = snapshot_dto.obtener_clientes();
    for (auto& cliente: clientes) {
        std::cout << "Cliente ID: " << cliente.id_cliente << "\n";
    }
}
