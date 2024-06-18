#include "cliente_enviador.h"

#include <iostream>
#include <vector>

ClienteEnviador::ClienteEnviador(Socket* socket, std::atomic<bool>& hablando,
                                 Queue<std::vector<char>>* cola_enviador):
        socket(socket),
        hablando(hablando),
        cola_enviador(cola_enviador),
        cliente_serializador(socket) {}

void ClienteEnviador::run() {
    bool cerrado = false;
    std::vector<char> bytes;
    try {
        while (!cerrado && hablando) {
            bytes = cola_enviador->pop();
            cliente_serializador.enviar_comando(cola_enviador->pop(), &cerrado);
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Se cerro la cola correctamente" << std::endl;
    }
    hablando = false;
}

void ClienteEnviador::stop() { hablando = false; }
