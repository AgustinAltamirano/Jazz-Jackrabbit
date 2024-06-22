#include "lobby_recibidor.h"

#include <iostream>

#include "../../common/liberror.h"

LobbyRecibidor::LobbyRecibidor(Socket* socket, std::atomic<bool>& sigo_hablando,
                               Queue<std::shared_ptr<ComandoDTO>>* cola_recibidor):
        sigo_hablando(sigo_hablando), cola_recibidor(cola_recibidor), lobby_protocolo(socket) {}

void LobbyRecibidor::run() {
    bool cerrado = false;
    while (sigo_hablando && !cerrado) {
        try {
            std::shared_ptr<ComandoDTO> comando = lobby_protocolo.obtener_comando(&cerrado);
            cola_recibidor->push(comando);
        } catch (const LibError& e) {
            sigo_hablando = false;
            std::cout << "Se perdió la conexión" << std::endl;
            break;
        }
    }
}

void LobbyRecibidor::stop() { sigo_hablando = false; }
