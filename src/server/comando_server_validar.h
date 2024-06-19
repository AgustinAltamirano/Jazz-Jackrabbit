#ifndef COMANDO_LOBBY_VALIDAR_H
#define COMANDO_LOBBY_VALIDAR_H

#include <string>

#include "../common/tipo_personaje.h"

#include "comando_server.h"


class ComandoLobbyValidar: public ComandoServer {
private:
    std::string nombre_escenario;

    bool es_valida;

public:
    ComandoLobbyValidar(int32_t& id_cliente, std::string nombre_escenario);

    explicit ComandoLobbyValidar(bool es_valida);

    std::string obtener_nombre_escenario();

    [[nodiscard]] bool obtener_es_valida() const;

    Queue<ComandoServer*>* ejecutar(GestorPartidas* gestor_partidas,
                                           Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                           int32_t id_cliente, bool& cerrado,
                                           ServidorProtocolo& servidor_serializador) override;

    ~ComandoLobbyValidar() override = default;
};

#endif
