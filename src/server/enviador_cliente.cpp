#include "enviador_cliente.h"

#include <memory>
#include <string>

#include "../common/comando_crear_dto.h"
#include "../common/comando_unir_dto.h"
#include "../common/comando_validar_dto.h"
#include "../common/validador_de_mapas.h"

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
        skt_cliente(skt_cliente),
        id_cliente(id_cliente) {
    cola_recibidor = nullptr;
    sigo_en_partida = true;
}

void EnviadorCliente::run() {
    servidor_serializador.enviar_id_cliente(id_cliente, &cerrado);
    inicio_recibidor_cliente();
    while (sigo_jugando) {
        try {
            while (sigo_en_partida && !cerrado) {
                std::shared_ptr<SnapshotDTO> snapshot_dto = cola_enviador.pop();

                std::vector<ClienteDTO>& clientes_dto = snapshot_dto->obtener_clientes();
                std::vector<BloqueEscenarioDTO>& bloques_dto =
                        snapshot_dto->obtener_bloques_escenario();

                uint8_t num_clientes = clientes_dto.size();
                uint8_t num_bloques = bloques_dto.size();

                auto tipo_escenario = static_cast<uint8_t>(snapshot_dto->obtener_tipo_escenario());
                auto fin_juego = snapshot_dto->es_fin_juego();


                bool skt_cerrado;

                skt_cliente->sendall(&num_clientes, sizeof(uint8_t), &skt_cerrado);
                skt_cliente->sendall(&num_bloques, sizeof(uint8_t), &skt_cerrado);
                skt_cliente->sendall(&tipo_escenario, sizeof(uint8_t), &skt_cerrado);
                skt_cliente->sendall(&fin_juego, sizeof(bool), &skt_cerrado);

                for (const auto& cliente_dto: clientes_dto) {
                    skt_cliente->sendall(&cliente_dto, sizeof(cliente_dto), &skt_cerrado);
                }

                for (const auto& bloque_dto: bloques_dto) {
                    skt_cliente->sendall(&bloque_dto, sizeof(bloque_dto), &skt_cerrado);
                }
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
    //    while (sigo_jugando) {
    try {
        int32_t codigo_partida;
        ComandoDTO* comando = servidor_deserializador.obtener_comando(&cerrado, id_cliente);
        if (comando->obtener_comando() == CREAR) {
            ComandoCrearDTO* crear_dto = dynamic_cast<ComandoCrearDTO*>(comando);
            std::string nombre_escenario = crear_dto->obtener_nombre_escenario();
            TipoPersonaje personaje = crear_dto->obtener_personaje();
            int8_t capacidad_partida = crear_dto->obtener_capacidad_partida();
            cola_recibidor =
                    gestor_partidas->crear_partida(&cola_enviador, nombre_escenario, id_cliente,
                                                   codigo_partida, personaje, capacidad_partida);
            // Si me devuelve un puntero nulo significa que no se pudo crear la partida
            if (cola_recibidor == nullptr) {
                servidor_serializador.enviar_error_crear_partida(&cerrado);
            } else {
                servidor_serializador.enviar_crear_partida(codigo_partida, &cerrado);
            }

        } else if (comando->obtener_comando() == UNIR) {
            ComandoUnirDTO* unir_dto = dynamic_cast<ComandoUnirDTO*>(comando);
            codigo_partida = unir_dto->obtener_codigo_partida();
            TipoPersonaje personaje = unir_dto->obtener_personaje();
            cola_recibidor = gestor_partidas->unir_partida(&cola_enviador, codigo_partida,
                                                           id_cliente, personaje);
            servidor_serializador.enviar_unir_partida((cola_recibidor != nullptr), &cerrado);
        } else if (comando->obtener_comando() == VALIDAR_ESCENARIO) {
            ComandoValidarDTO* validar_dto = dynamic_cast<ComandoValidarDTO*>(comando);
            const std::string nombre_escenario = validar_dto->obtener_nombre_escenario();
            bool es_valido = validador_de_mapas::validar_mapa_custom(nombre_escenario);
            servidor_serializador.enviar_validar_escenario(es_valido, &cerrado);
        }
        delete comando;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        sigo_en_partida = false;
        sigo_jugando = false;
        return;
    }
    //    }
    recibidor_cliente.establecer_cola_recibidor(cola_recibidor);
    recibidor_cliente.start();
}

void EnviadorCliente::stop() {
    sigo_en_partida = false;
    sigo_jugando = false;
}
