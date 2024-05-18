#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <vector>
#include <string>
#include "cliente_protocolo.h"
#include "stdin_handler.h"

class Cliente {
private:
    ProtocoloCliente protocolo_cliente;
    StdinHandler stdin_handler;

    void enviar_mensaje(std::vector<std::string> &mensaje);

    void leer_mensajes(int cantidad);

public:
    Cliente(const std::string &hostname, const std::string &servname);

    void run();

    Cliente(const Cliente &) = delete;

    Cliente &operator=(const Cliente &) = delete;
};

#endif  // CLIENTE_H_
