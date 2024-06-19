#include "recibidor_cliente.h"

#include <iostream>

#include "src/common/liberror.h"
#include "src/common/validador_de_mapas.h"

RecibidorCliente::RecibidorCliente(Socket* socket, std::atomic<bool>& sigo_en_partida,
                                   int32_t& id_cliente, GestorPartidas* gestor_partidas,
                                   Queue<std::shared_ptr<SnapshotDTO>>& cola_cliente):
        id_cliente(id_cliente),
        sigo_en_partida(sigo_en_partida),
        servidor_protocolo(socket),
        gestor_partidas(gestor_partidas),
        cola_enviador(cola_cliente) {
    cola_recibidor = nullptr;
}

void RecibidorCliente::inicio_recibidor_cliente() {
    try {
        int32_t codigo_partida;
        ComandoDTO* comando = servidor_protocolo.obtener_comando(&cerrado, id_cliente);
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
                servidor_protocolo.enviar_error_crear_partida(&cerrado);
            } else {
                servidor_protocolo.enviar_crear_partida(codigo_partida, &cerrado);
            }

        } else if (comando->obtener_comando() == UNIR) {
            ComandoUnirDTO* unir_dto = dynamic_cast<ComandoUnirDTO*>(comando);
            codigo_partida = unir_dto->obtener_codigo_partida();
            TipoPersonaje personaje = unir_dto->obtener_personaje();
            cola_recibidor = gestor_partidas->unir_partida(&cola_enviador, codigo_partida,
                                                           id_cliente, personaje);
            servidor_protocolo.enviar_unir_partida((cola_recibidor != nullptr), &cerrado);
        } else if (comando->obtener_comando() == VALIDAR_ESCENARIO) {
            ComandoValidarDTO* validar_dto = dynamic_cast<ComandoValidarDTO*>(comando);
            const std::string nombre_escenario = validar_dto->obtener_nombre_escenario();
            bool es_valido = validador_de_mapas::validar_mapa_custom(nombre_escenario);
            servidor_protocolo.enviar_validar_escenario(es_valido, &cerrado);
        }
        delete comando;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        sigo_en_partida = false;
        return;
    }
    establecer_cola_recibidor(cola_recibidor);
    this->start();
}

void RecibidorCliente::run() {
    bool cerrado = false;
    while (sigo_en_partida && !cerrado) {
        try {
            ComandoDTO* nuevo_comando = servidor_protocolo.obtener_comando(&cerrado, id_cliente);
            try {
                cola_recibidor->push(nuevo_comando);
            } catch (const ClosedQueue& e) {
                delete nuevo_comando;
                std::cout << "Juego finalizado" << std::endl;
                break;
            }
        } catch (const std::runtime_error& e) {
            sigo_en_partida = false;
            std::cout << "Se desconecto el cliente" << std::endl;
            break;
        }
    }
    sigo_en_partida = false;
    cola_recibidor->close();
}

void RecibidorCliente::establecer_cola_recibidor(Queue<ComandoDTO*>* cola_recibidor) {
    this->cola_recibidor = cola_recibidor;
}
