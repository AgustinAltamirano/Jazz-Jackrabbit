#include "servidor.h"

#include "aceptador.h"

Servidor::Servidor(char* servname): skt_servidor(servname), aceptador(&skt_servidor) {
    aceptador.start();
}

void Servidor::run() {
    while (std::cin.get() != 'q') {}
    aceptador.stop();
    aceptador.join();
}
