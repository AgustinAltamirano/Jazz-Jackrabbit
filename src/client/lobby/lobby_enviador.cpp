#include "lobby_enviador.h"

#include <iostream>
#include <vector>


LobbyEnviador::LobbyEnviador(Socket* socket, std::atomic<bool>& sigo_hablando,
                             Queue<std::shared_ptr<ComandoDTO>>* cola_enviador):
        socket(socket),
        sigo_hablando(sigo_hablando),
        cola_enviador(cola_enviador),
        lobby_protocolo(socket) {}

void LobbyEnviador::run() {
    bool cerrado = false;
    try {
        while (!cerrado && sigo_hablando) {
            lobby_protocolo.enviar_comando(cola_enviador->pop(), &cerrado);
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    }
    sigo_hablando = false;
}

void LobbyEnviador::stop() { sigo_hablando = false; }
