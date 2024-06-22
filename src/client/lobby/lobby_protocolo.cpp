#include "lobby_protocolo.h"

#include <iostream>
#include <memory>

#include <arpa/inet.h>

#include "../../common/tipo_comando.h"

LobbyProtocolo::LobbyProtocolo(SocketAbstracto* socket): socket(socket) {}

std::shared_ptr<ComandoDTO> LobbyProtocolo::obtener_comando(bool* cerrado) {
    char codigo_comando = 0;
    socket->recvall(&codigo_comando, 1, cerrado);
    if (*cerrado) {
        throw std::runtime_error("Se cerro el socket esperando un comando");
    }
    TipoComando tipo_comando = static_cast<TipoComando>(codigo_comando);
    switch (tipo_comando) {
        case CREAR:
            return deserializar_crear_partida(cerrado);
        case UNIR:
            return deserializar_unir_partida(cerrado);
        case VALIDAR_ESCENARIO:
            return deserializar_validar_escenario(cerrado);
        default:
            std::cout << "ERROR de comando";
            throw std::invalid_argument("no se encontro el caso en el deserializador del servidor");
    }
}

std::shared_ptr<ComandoCrearDTO> LobbyProtocolo::deserializar_crear_partida(bool* cerrado) {
    int32_t codigo_partida;
    socket->recvall(&codigo_partida, 4, cerrado);
    codigo_partida = ntohl(codigo_partida);
    *cerrado = true;
    return std::make_shared<ComandoCrearDTO>(codigo_partida);
}

std::shared_ptr<ComandoUnirDTO> LobbyProtocolo::deserializar_unir_partida(bool* cerrado) {
    bool unio;
    socket->recvall(&unio, 1, cerrado);
    *cerrado = unio;
    return std::make_shared<ComandoUnirDTO>(unio);
}

std::shared_ptr<ComandoValidarDTO> LobbyProtocolo::deserializar_validar_escenario(bool* cerrado) {
    bool es_valida;
    socket->recvall(&es_valida, 1, cerrado);
    return std::make_shared<ComandoValidarDTO>(es_valida);
}

int32_t LobbyProtocolo::obtener_id_cliente() {
    int32_t id_cliente;
    bool cerrado = false;
    socket->recvall(&id_cliente, sizeof(int), &cerrado);
    id_cliente = ntohl(id_cliente);
    return id_cliente;
}

void LobbyProtocolo::enviar_comando(const std::shared_ptr<ComandoDTO>& comando, bool* cerrado) {
    std::vector<char> buffer;
    buffer = comando->serializar();
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}
