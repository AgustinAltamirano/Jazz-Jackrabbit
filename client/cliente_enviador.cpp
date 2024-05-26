#include "cliente_enviador.h"

#include <iostream>
#include <vector>

ClienteEnviador::ClienteEnviador(Socket *socket, std::atomic<bool> &hablando,
                                 Queue<std::vector<char>> *cola_enviador) :
        socket(socket), hablando(hablando), cola_enviador(cola_enviador) {}

void ClienteEnviador::run() {
    bool cerrado = false;
    std::vector<char> bytes;
    try {
        while (!cerrado && hablando) {
            bytes = cola_enviador->pop();
            socket->sendall(bytes.data(), bytes.size(), &cerrado);
        }
    } catch (const ClosedQueue &e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    }
    hablando = false;
}
