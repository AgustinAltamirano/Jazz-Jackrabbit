#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#include "../../common/queue.h"
#include "../../common/thread.h"

#include "administrador_vista_juego.h"
#include "snapshot_dto.h"

class TestSDL final: public Thread {
private:
    Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones;
    Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots;

public:
    TestSDL(Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones,
            Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots):
            cola_acciones(cola_acciones), cola_snapshots(cola_snapshots) {}

    TestSDL(const TestSDL&) = delete;
    TestSDL& operator=(const TestSDL&) = delete;

    void run() override {
        const auto snapshot = std::make_shared<SnapshotDTO_provisorio>(ESCENARIO1);
        snapshot->agregar_id_cliente(3);

        BloqueEscenarioDTO bloque_dto_piso(20, 300, 850, 64, 0, PISO);
        snapshot->agregar_bloque_escenario(std::move(bloque_dto_piso));

        BloqueEscenarioDTO bloque_dto_pared1(20, 44, 64, 256, 0, PARED);
        snapshot->agregar_bloque_escenario(std::move(bloque_dto_pared1));

        BloqueEscenarioDTO bloque_dto_pared2(800, 44, 64, 256, 0, PARED);
        snapshot->agregar_bloque_escenario(std::move(bloque_dto_pared2));

        BloqueEscenarioDTO bloque_dto_techo(20, -20, 850, 64, 0, TECHO);
        snapshot->agregar_bloque_escenario(std::move(bloque_dto_techo));

        cola_snapshots.try_push(snapshot);

        while (_keep_running) {
            for (int32_t x = 150; x < 600; x += 5) {
                auto snapshot_jugador = std::make_shared<SnapshotDTO_provisorio>(ESCENARIO1);
                snapshot_jugador->agregar_id_cliente(3);
                ClienteDTO cliente_dto(1, JAZZ, 150, 205, false, IDLE, 100, 38, ARMA1, 2);
                snapshot_jugador->agregar_cliente(std::move(cliente_dto));

                ClienteDTO cliente_dto_2(2, JAZZ, 700, 205, false, IDLE, 100, 38, ARMA1, 2);
                snapshot_jugador->agregar_cliente(std::move(cliente_dto_2));

                ClienteDTO cliente_dto_3(3, JAZZ, x, 235, false, CORRER, 100, 38, ARMA1, 2);
                snapshot_jugador->agregar_cliente(std::move(cliente_dto_3));

                cola_snapshots.try_push(snapshot_jugador);
                std::this_thread::sleep_for(std::chrono::milliseconds(33));
            }

            for (int32_t x = 600; x >= 150; x -= 5) {
                auto snapshot_jugador = std::make_shared<SnapshotDTO_provisorio>(ESCENARIO1);
                snapshot_jugador->agregar_id_cliente(3);
                ClienteDTO cliente_dto(1, JAZZ, 150, 205, false, IDLE, 100, 38, ARMA1, 2);
                snapshot_jugador->agregar_cliente(std::move(cliente_dto));

                ClienteDTO cliente_dto_2(2, JAZZ, 700, 205, false, IDLE, 100, 38, ARMA1, 2);
                snapshot_jugador->agregar_cliente(std::move(cliente_dto_2));

                ClienteDTO cliente_dto_3(3, JAZZ, x, 235, true, CORRER, 100, 38, ARMA1, 2);
                snapshot_jugador->agregar_cliente(std::move(cliente_dto_3));

                cola_snapshots.try_push(snapshot_jugador);
                std::this_thread::sleep_for(std::chrono::milliseconds(33));
            }
        }
    }

    ~TestSDL() override { Thread::join(); }
};


int main() {
    Queue<std::shared_ptr<AccionJuegoDTO>> cola_acciones(30);
    Queue<std::shared_ptr<SnapshotDTO_provisorio>> cola_snapshots(30);
    TestSDL test(cola_acciones, cola_snapshots);
    test.start();

    AdministradorVistaJuego admin("Test", cola_acciones, cola_snapshots);
    admin.run();

    // Comentar las dos líneas de arriba y descomentar las siguientes dos para forzar un leak de
    // memoria
    // auto* leak = new AdministradorVistaJuego("Leak", cola_acciones, cola_snapshots);
    // leak->run();

    test.stop();
    return 0;
}
