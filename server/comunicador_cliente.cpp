#include <utility>
#include "comunicador_cliente.h"
#include "recibidor_cliente.h"

ComunicadorCliente::ComunicadorCliente(Socket skt_jugador,
                                       MonitorPartidas &monitor_partidas) :
        cola_jugador(1000),
        juego(monitor_partidas),
        protocolo(std::move(skt_jugador),
                  juego,
                  cola_jugador) {}

void ComunicadorCliente::run() {
    RecibidorCliente thread_recibidor(protocolo);
    thread_recibidor.start();
    enviar_mensaje();
    thread_recibidor.join();
}

void ComunicadorCliente::enviar_mensaje() {
    try {
        while (sigo_vivo) {
            protocolo.enviar_mensaje();
            sigo_vivo = protocolo.sigue_vivo();
        }
    } catch (const std::exception &err) {
        if (sigo_vivo) {
            std::cerr << "Excepcion capturada: " << err.what() << "\n";
        }
    }
}

bool ComunicadorCliente::sigue_vivo() {
    return protocolo.sigue_vivo();
}

void ComunicadorCliente::kill() {
    cola_jugador.close();
    sigo_vivo = false;
    protocolo.cerrar_todo();
}
