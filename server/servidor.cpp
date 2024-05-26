#include <sys/socket.h>
#include "servidor.h"
#include "aceptador.h"

Servidor::Servidor(char *servname) :
        skt_servidor(servname), aceptador(&skt_servidor) {
    aceptador.start();
}

void Servidor::run() {
    while (std::cin.get() != 'q') {}
    skt_servidor.shutdown(SHUT_RDWR);
    skt_servidor.close();
    aceptador.join();
}
