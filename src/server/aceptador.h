#ifndef ACEPTADOR_H_
#define ACEPTADOR_H_

#include <atomic>
#include <list>
#include <string>
#include <vector>

#include "../common/socket.h"
#include "../common/thread.h"

#include "comunicador_cliente.h"
#include "gestor_partidas.h"

class Aceptador: public Thread {
private:
    Socket* skt_servidor;
    std::list<ComunicadorCliente*> clientes;
    GestorPartidas gestor_partidas;
    std::atomic<bool> sigo_jugando{true};

    void limpiar_clientes();

    void eliminar_todos_clientes();


public:
    explicit Aceptador(Socket* skt_servidor);

    void run() override;

    void stop() override;

    ~Aceptador() override;

    Aceptador(const Aceptador&) = delete;

    Aceptador& operator=(const Aceptador&) = delete;
};

#endif  // ACEPTADOR_H_
