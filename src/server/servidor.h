#ifndef SERVIDOR_H_
#define SERVIDOR_H_


#include <string>
#include "../common/socket.h"
#include "aceptador.h"

class Servidor {
private:
    Socket skt_servidor;
    Aceptador aceptador;

public:
    explicit Servidor(char* servname);

    void run();

    Servidor(const Servidor &) = delete;

    Servidor &operator=(const Servidor &) = delete;
};

#endif  // SERVIDOR_H_
