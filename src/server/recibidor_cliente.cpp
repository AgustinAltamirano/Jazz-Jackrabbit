#include "recibidor_cliente.h"

#include <iostream>

#include "src/common/liberror.h"
#include "src/common/validador_de_mapas.h"

#include "comando_server_crear.h"
#include "comando_server_unir.h"
#include "comando_server_validar.h"

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

bool RecibidorCliente::inicio_recibidor_cliente() {
    bool sigo_en_el_lobby = true;
    while (sigo_en_el_lobby) {
        try {
            int32_t codigo_partida;
            auto comando = servidor_protocolo.obtener_comando(&cerrado, id_cliente);

            cola_recibidor =
                    comando->ejecutar(gestor_partidas, cola_enviador, cerrado, servidor_protocolo);

            if (cola_recibidor != nullptr) {
                sigo_en_el_lobby = false;
            }
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            sigo_en_partida = false;
            return false;
        }
    }
    establecer_cola_recibidor(cola_recibidor);
    this->start();
    return true;
}

void RecibidorCliente::run() {
    bool cerrado = false;
    while (sigo_en_partida && !cerrado) {
        try {
            auto nuevo_comando =
                    servidor_protocolo.obtener_comando(&cerrado, id_cliente);
            try {
                    cola_recibidor->push(nuevo_comando.release());
            } catch (const ClosedQueue& e) {
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

void RecibidorCliente::establecer_cola_recibidor(Queue<ComandoServer*>* cola_recibidor) {
    this->cola_recibidor = cola_recibidor;
}
