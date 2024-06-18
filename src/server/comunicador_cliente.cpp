#include "comunicador_cliente.h"

#include <utility>

#include <sys/socket.h>

ComunicadorCliente::ComunicadorCliente(Socket socket, GestorPartidas* gestor_partidas,
                                       int32_t id_cliente):
        id_cliente(id_cliente),
        skt_cliente(std::move(socket)),
        cola_cliente(10000),
        gestor_partidas(gestor_partidas),
        enviador_cliente(&skt_cliente, std::ref(sigo_en_partida), id_cliente, cola_cliente),
        recibidor_cliente(&skt_cliente, std::ref(sigo_en_partida), id_cliente, gestor_partidas,cola_cliente),
        sigo_en_partida(true) {
    enviador_cliente.start();
    recibidor_cliente.inicio_recibidor_cliente();
}

void ComunicadorCliente::matar_cliente() {
    sigo_en_partida = false;
    enviador_cliente.cerrar_cola();
    enviador_cliente.join();
    skt_cliente.shutdown(SHUT_RDWR);
    skt_cliente.close();
    recibidor_cliente.join();
    gestor_partidas->borrar_cliente(id_cliente);
}

bool ComunicadorCliente::sigue_en_partida() {
    return enviador_cliente.is_alive() && recibidor_cliente.is_alive();
}

