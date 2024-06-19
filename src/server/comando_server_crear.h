#ifndef COMANDO_LOBBY_CREAR_H
#define COMANDO_LOBBY_CREAR_H

#include <string>

#include "../common/tipo_personaje.h"

#include "comando_server.h"


class ComandoLobbyCrear: public ComandoServer {
private:
    std::string nombre_escenario;

    int32_t codigo_partida;

    TipoPersonaje personaje;

    int8_t capacidad_partida{};

public:
    ComandoLobbyCrear(int32_t& id_cliente, std::string nombre_escenario, TipoPersonaje personaje,
                    int8_t capacidad_partida);

    explicit ComandoLobbyCrear(int32_t codigo_partida);

    [[nodiscard]] int32_t obtener_codigo_partida() const;

    Queue<ComandoServer*>* ejecutar(GestorPartidas* gestor_partidas,
                  Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                  int32_t id_cliente, bool& cerrado,
                  ServidorProtocolo& servidor_serializador) override;

    ~ComandoLobbyCrear() override = default;
};

#endif
