#include "lobby_recibidor.h"

#include <iostream>

LobbyRecibidor::LobbyRecibidor(Socket *socket, std::atomic<bool> &sigo_hablando,
                               Queue<ComandoDTO *> *cola_recibidor) : sigo_hablando(sigo_hablando),
                                                                      cola_recibidor(cola_recibidor),
                                                                      lobby_deserializador(socket) {}

void LobbyRecibidor::run() {
    bool cerrado = false;
    while (sigo_hablando && !cerrado) {
        try {
            ComandoDTO *comando = lobby_deserializador.obtener_comando(&cerrado);
            if (comando->obtener_comando() == COMENZAR) {
                ComandoComenzarDTO *comenzar_dto = dynamic_cast<ComandoComenzarDTO *>(comando);
                if (comenzar_dto->obtener_empezo())
                    sigo_hablando = false;
            }
            cola_recibidor->push(comando);
        }
        catch (const std::runtime_error &e) {
            sigo_hablando = false;
            std::cout << "Se desconecto el cliente" << std::endl;
            break;
        }
    }
}

void LobbyRecibidor::kill() {
    sigo_hablando = false;
}

bool LobbyRecibidor::still_alive() {
    return sigo_hablando;
}
