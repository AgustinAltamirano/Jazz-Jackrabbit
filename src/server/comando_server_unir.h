#ifndef COMANDO_LOBBY_UNIR_H
#define COMANDO_LOBBY_UNIR_H

#include <cstdint>

#include "../common/tipo_personaje.h"

#include "comando_server.h"

class ComandoLobbyUnir: public ComandoServer {
private:
    int32_t codigo_partida;

    TipoPersonaje personaje;

    bool unio;

public:
    ComandoLobbyUnir(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje);

    explicit ComandoLobbyUnir(bool unio);

    [[nodiscard]] int32_t obtener_codigo_partida() const;

    TipoPersonaje obtener_personaje();

    [[nodiscard]] bool obtener_unio() const;

    Queue<ComandoServer*>* ejecutar(GestorPartidas* gestor_partidas,
                  Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                  int32_t id_cliente, bool& cerrado,
                  ServidorProtocolo& servidor_serializador) override;
};

#endif
