#ifndef LOBBY_H
#define LOBBY_H

#include <optional>
#include <string>
#include <vector>

#include "../../common/socket.h"
#include "../../common/tipo_escenario.h"
#include "../../common/tipo_personaje.h"

#include "lobby_enviador.h"
#include "lobby_protocolo.h"
#include "lobby_recibidor.h"

class Lobby {
private:
    int32_t id_cliente;

    Socket socket;

    std::atomic<bool> sigo_hablando;

    LobbyEnviador lobby_enviador;

    LobbyRecibidor lobby_recibidor;

    LobbyProtocolo lobby_protocolo;

    Queue<ComandoDTO*> cola_enviador;

    Queue<ComandoDTO*> cola_recibidor;

    bool obtener_unir();

    bool obtener_validar_escenario();

public:
    Lobby(const std::string& hostname, const std::string& servname);

    int32_t crear_partida(const std::string& nombre_escenario, const TipoPersonaje& personaje,
                          const int8_t& capacidad_partida);

    bool unir_partida(const int32_t& codigo_partida, const TipoPersonaje& personaje);

    bool validar_escenario(const std::string& nombre_escenario);

    void salir_lobby();

    Socket move_socket();

    int32_t obtener_crear();

    [[nodiscard]] int obtener_id_cliente() const;

    void cerrar();
};

#endif
