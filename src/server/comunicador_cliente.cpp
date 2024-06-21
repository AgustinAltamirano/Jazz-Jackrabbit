#include "comunicador_cliente.h"

#include <memory>
#include <utility>

#include <sys/socket.h>
#include <syslog.h>

#include "../common/snapshot_dto.h"
#include "src/common/liberror.h"

ComunicadorCliente::ComunicadorCliente(Socket socket, GestorPartidas* gestor_partidas,
                                       int32_t id_cliente):
        id_cliente(id_cliente),
        skt_cliente(std::move(socket)),
        cola_cliente(10000),
        gestor_partidas(gestor_partidas),
        enviador_cliente(&skt_cliente, std::ref(sigo_en_partida), id_cliente, cola_cliente),
        recibidor_cliente(&skt_cliente, std::ref(sigo_en_partida), id_cliente, gestor_partidas,
                          cola_cliente),
        sigo_en_partida(true) {
    iniciar_cliente();
}

void ComunicadorCliente::iniciar_cliente() {
    try {
        enviador_cliente.start();
        recibidor_cliente.start();
    } catch (const LibError& err) {
        syslog(LOG_ERR, "Salida prematura de usuario: %s", err.what());
        return;
    }
}

void ComunicadorCliente::limpiar_cliente() {
    sigo_en_partida = false;
    enviador_cliente.cerrar_cola();
    enviador_cliente.join();
    skt_cliente.close();
    recibidor_cliente.join();
}

void ComunicadorCliente::matar_cliente() {
    skt_cliente.shutdown(SHUT_RD);
    limpiar_cliente();
}

bool ComunicadorCliente::sigue_en_partida() const {
    return enviador_cliente.is_alive() && recibidor_cliente.is_alive();
}
