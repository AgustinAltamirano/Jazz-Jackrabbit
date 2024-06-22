#ifndef ACEPTADOR_H_
#define ACEPTADOR_H_

#include <atomic>
#include <map>
#include <memory>
#include <string>

#include "../common/socket.h"
#include "../common/thread.h"

#include "comunicador_cliente.h"
#include "gestor_partidas.h"

class Aceptador: public Thread {
private:
    Socket* skt_servidor;
    std::map<int32_t, ComunicadorCliente> clientes;
    GestorPartidas gestor_partidas;
    std::atomic<bool> sigo_jugando{true};
    int32_t proximo_id_cliente;

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
