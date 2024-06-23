#include "recibidor_cliente.h"

#include <iostream>
#include <memory>

#include "src/common/liberror.h"

#include "comando_server_crear.h"
#include "comando_server_unir.h"
#include "comando_server_validar.h"

RecibidorCliente::RecibidorCliente(Socket* socket, std::atomic<bool>& sigo_en_partida,
                                   int32_t& id_cliente, GestorPartidas* gestor_partidas,
                                   Queue<std::shared_ptr<SnapshotDTO>>& cola_cliente):
        id_cliente(id_cliente),
        sigo_en_partida(sigo_en_partida),
        cliente_desconectado(false),
        servidor_protocolo(socket),
        gestor_partidas(gestor_partidas),
        cola_enviador(cola_cliente) {
    cola_recibidor = nullptr;
}

bool RecibidorCliente::inicio_recibidor_cliente() {
    bool sigo_en_el_lobby = true;
    while (sigo_en_el_lobby) {
        try {
            auto comando = servidor_protocolo.obtener_comando(&cerrado, id_cliente);

            cola_recibidor =
                    comando->ejecutar(gestor_partidas, cola_enviador, cerrado, servidor_protocolo);

            if (cola_recibidor != nullptr) {
                sigo_en_el_lobby = false;
            }
        } catch (const LibError& e) {
            std::cout << e.what() << std::endl;
            sigo_en_partida = false;
            return false;
        }
    }
    establecer_cola_recibidor(cola_recibidor);
    return true;
}

void RecibidorCliente::run() {
    inicio_recibidor_cliente();
    bool cliente_cerrado = false;
    while (sigo_en_partida && !cliente_cerrado) {
        try {
            auto nuevo_comando = servidor_protocolo.obtener_comando(&cerrado, id_cliente);
            try {
                cola_recibidor->push(nuevo_comando);
            } catch (const ClosedQueue& e) {
                std::cout << "Juego finalizado" << std::endl;
                sigo_en_partida = false;
                return;
            }
        } catch (const LibError& e) {
            sigo_en_partida = false;
            cliente_desconectado = true;
            std::cout << "Se desconecto el cliente" << std::endl;
            gestor_partidas->borrar_cliente(id_cliente);
            return;
        }
    }
    sigo_en_partida = false;
}

void RecibidorCliente::establecer_cola_recibidor(
        Queue<std::shared_ptr<ComandoServer>>* queue_recibidor) {
    this->cola_recibidor = queue_recibidor;
}

bool RecibidorCliente::esta_desconectado() const {
    return cliente_desconectado;
}
