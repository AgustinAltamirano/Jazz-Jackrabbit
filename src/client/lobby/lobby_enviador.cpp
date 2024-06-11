#include "lobby_enviador.h"

#include <iostream>
#include <vector>


LobbyEnviador::LobbyEnviador(Socket* socket, std::atomic<bool>& sigo_hablando,
                             Queue<std::vector<char>>* cola_enviador):
        socket(socket), sigo_hablando(sigo_hablando), cola_enviador(cola_enviador) {}

void LobbyEnviador::run() {
    bool cerrado = false;
    std::vector<char> bytes;
    try {
        while (!cerrado && sigo_hablando) {
            bytes = cola_enviador->pop();
            socket->sendall(bytes.data(), bytes.size(), &cerrado);
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    }
    sigo_hablando = false;
}

void LobbyEnviador::stop() { sigo_hablando = false; }
