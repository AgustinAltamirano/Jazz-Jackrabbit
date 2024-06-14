#include "comunicador_cliente.h"

#include <iostream>
#include <utility>

#include <sys/socket.h>

ComunicadorCliente::ComunicadorCliente(Socket socket, GestorPartidas* gestor_partidas,
                                       int32_t id_cliente):
        id_cliente(id_cliente),
        enviador_cliente(&skt_cliente, std::ref(sigo_en_partida), std::ref(sigo_jugando),
                         gestor_partidas, id_cliente) {
    this->skt_cliente = std::move(socket);
    enviador_cliente.start();
    sigo_en_partida = true;
    sigo_jugando = true;
}

void ComunicadorCliente::stop() {
    sigo_en_partida = false;
    sigo_jugando = false;
    skt_cliente.shutdown(SHUT_RDWR);
    skt_cliente.close();
    enviador_cliente.cerrar_cola();
}

void ComunicadorCliente::join() {
    enviador_cliente.join();
    enviador_cliente.join_recibidor_cliente();
}

void ComunicadorCliente::run() {}
