#include "cliente_serializador.h"

ClienteSerializador::ClienteSerializador(Socket* socket): socket(socket) {}

std::vector<char> ClienteSerializador::serializar_comando(const TipoComando& comando) {
    std::vector<char> buffer;
    buffer.push_back(comando);
    return buffer;
}

void ClienteSerializador::enviar_comando(std::vector<char> bytes, bool* cerrado) {
    socket->sendall(bytes.data(), bytes.size(), cerrado);
}
