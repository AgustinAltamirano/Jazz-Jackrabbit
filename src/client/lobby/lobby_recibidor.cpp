#include "lobby_recibidor.h"

#include <iostream>

LobbyRecibidor::LobbyRecibidor(Socket* socket, std::atomic<bool>& sigo_hablando,
                               Queue<ComandoDTO*>* cola_recibidor):
        sigo_hablando(sigo_hablando),
        cola_recibidor(cola_recibidor),
        lobby_deserializador(socket) {}

void LobbyRecibidor::run() {
    bool cerrado = false;
    while (sigo_hablando && !cerrado) {
        try {
            ComandoDTO* comando = lobby_deserializador.obtener_comando(&cerrado);
            cola_recibidor->push(comando);
        } catch (const std::runtime_error& e) {
            sigo_hablando = false;
            std::cout << "Se desconecto el cliente" << std::endl;
            break;
        }
    }
}

void LobbyRecibidor::stop() { sigo_hablando = false; }
