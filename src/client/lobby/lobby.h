#ifndef LOBBY_H
#define LOBBY_H

#include "../../common/socket.h"
#include "lobby_enviador.h"
#include "lobby_recibidor.h"
#include "lobby_serializador.h"
#include "lobby_deserializador.h"
#include <optional>
#include <vector>
#include <string>

class Lobby {
private:
    int32_t id_cliente;

    Socket socket;

    std::atomic<bool> sigo_hablando;

    LobbyEnviador lobby_enviador;

    LobbyRecibidor lobby_recibidor;

    LobbySerializador lobby_serializador;

    Queue<std::vector<char>> cola_enviador;

    Queue<ComandoDTO *> cola_recibidor;

public:

    Lobby(const std::string &hostname, const std::string &servname);

    bool crear_partida(const int8_t &capacidad_partida);

    bool unir_partida(const int32_t &codigo_partida);

    void comenzar();

    void cerrar();

    void salir_lobby();

    Socket move_socket();

    int32_t obtener_crear();

    bool obtener_unir();

    int obtener_id_cliente();
};

#endif
