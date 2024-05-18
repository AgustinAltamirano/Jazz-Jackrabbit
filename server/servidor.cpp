#include "servidor.h"
#include "aceptador_cliente.h"

Servidor::Servidor(std::string &servname) :
        servname(servname) {}

void Servidor::run() {
    AceptadorCliente aceptador_cliente(servname);
    aceptador_cliente.start();
    while (std::cin.get() != 'q') {}
    aceptador_cliente.kill();
    aceptador_cliente.join();
}
