#include "enviador_cliente.h"

#include <string>

#include "../common/comando_crear_dto.h"
#include "../common/comando_unir_dto.h"

EnviadorCliente::EnviadorCliente(Socket* skt_cliente, std::atomic<bool>& sigo_en_partida,
                                 std::atomic<bool>& sigo_jugando, GestorPartidas* gestor_partidas,
                                 int32_t& id_cliente):
        sigo_en_partida(sigo_en_partida),
        sigo_jugando(sigo_jugando),
        cola_enviador(10000),
        recibidor_cliente(skt_cliente, sigo_en_partida, sigo_jugando, id_cliente, cola_enviador),
        gestor_partidas(gestor_partidas),
        servidor_deserializador(skt_cliente),
        servidor_serializador(skt_cliente),
        id_cliente(id_cliente) {
    cola_recibidor = nullptr;
    sigo_en_partida = true;
}

void EnviadorCliente::run() {
    servidor_serializador.enviar_id_cliente(id_cliente, &cerrado);
    while (sigo_jugando) {
        inicio_recibidor_cliente();
        try {
            while (sigo_en_partida && !cerrado) {
                SnapshotDTO snapshot_dto = cola_enviador.pop();
                servidor_serializador.enviar_snapshot(snapshot_dto, &cerrado);
            }
        } catch (const ClosedQueue& e) {
            std::cout << "Se cerro la cola correctamente" << std::endl;
        }
        sigo_en_partida = false;
        sigo_jugando = false;
        // Si esta asociada a una partida lo elimino de la partida
        if (cola_recibidor != nullptr)
            gestor_partidas->borrar_cliente(
                    id_cliente);  // Elimino al jugador de la partida en la que estaba
    }
}

void EnviadorCliente::join_recibidor_cliente() {
    // Si esta asociado a una partida es porque se lanzo el thread.
    if (cola_recibidor != nullptr) {
        recibidor_cliente.join();
    }
}

void EnviadorCliente::cerrar_cola() { cola_enviador.close(); }

void EnviadorCliente::inicio_recibidor_cliente() {
    int32_t codigo_partida;
    while (sigo_jugando) {
        try {
            ComandoDTO* comando = servidor_deserializador.obtener_comando(&cerrado, id_cliente);
            if (comando->obtener_comando() == CREAR) {
                ComandoCrearDTO* crear_dto = dynamic_cast<ComandoCrearDTO*>(comando);
                int8_t capacidad_partida = crear_dto->obtener_capacidad_partida();
                cola_recibidor = gestor_partidas->crear_partida(&cola_enviador, id_cliente,
                                                                codigo_partida, capacidad_partida);
                // Si me devuelve un puntero nulo significa que no se pudo crear la partida
                if (cola_recibidor == nullptr)
                    servidor_serializador.enviar_error_crear_partida(&cerrado);
                else
                    servidor_serializador.enviar_crear_partida(codigo_partida, &cerrado);
            } else if (comando->obtener_comando() == UNIR) {
                ComandoUnirDTO* unir_dto = dynamic_cast<ComandoUnirDTO*>(comando);
                codigo_partida = unir_dto->obtener_codigo_partida();
                cola_recibidor =
                        gestor_partidas->unir_partida(&cola_enviador, codigo_partida, id_cliente);
                servidor_serializador.enviar_unir_partida((cola_recibidor != nullptr), &cerrado);
            } else if (comando->obtener_comando() == COMENZAR) {
                servidor_serializador.enviar_iniciar_juego(cola_recibidor != nullptr, &cerrado);
                if (cola_recibidor != nullptr) {
                    delete comando;
                    sigo_en_partida = true;
                    break;
                }
            }
            delete comando;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            sigo_en_partida = false;
            sigo_jugando = false;
            return;
        }
    }
    recibidor_cliente.establecer_cola_recibidor(cola_recibidor);
    recibidor_cliente.start();
}

void EnviadorCliente::kill() {
    sigo_en_partida = false;
    sigo_jugando = false;
}

bool EnviadorCliente::still_alive() { return sigo_jugando; }
