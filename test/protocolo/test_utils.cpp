#include <memory>

#include "common/snapshot_dto.h"
#include "common/socket_dummy.h"

std::shared_ptr<SnapshotDTO> crear_snapshot_test() {
    std::shared_ptr<SnapshotDTO> snapshot = std::make_shared<SnapshotDTO>();
    snapshot->establecer_tipo_escenario(ESCENARIO_CASTLE);
    snapshot->agregar_tiempo_restante(5);
    snapshot->establecer_fin_juego(false);
    snapshot->establecer_hubo_disparo(true);
    snapshot->establecer_hubo_herido(false);
    snapshot->establecer_hubo_muerte(true);

    BloqueEscenarioDTO bloque_escenario(32, 32, 5, 5, 0, PARED);
    snapshot->agregar_bloque_escenario(bloque_escenario);

    ClienteDTO cliente(1, JAZZ, 64, 64, false, CORRER, 10, 100, INFINITA, 0);
    snapshot->agregar_cliente(cliente);

    BalaDTO bala(10, 10, ARMA1, false);
    snapshot->agregar_bala(bala);

    EnemigoDTO enemigo(1, 15, 15, 5, 10, MURCIELAGO, false);
    snapshot->agregar_enemigo(enemigo);

    RecogibleDTO recogible(30, 30, 1, 1, MONEDA_AGARRABLE);
    snapshot->agregar_recogible(recogible);

    return snapshot;
}
