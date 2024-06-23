#ifndef COMANDO_LOBBY_UNIR_H
#define COMANDO_LOBBY_UNIR_H

#include <cstdint>

#include "../common/tipo_personaje.h"

#include "comando_server.h"

class ComandoServerUnir: public ComandoServer {
private:
    int32_t id_cliente;

    int32_t codigo_partida;

    TipoPersonaje personaje;

public:
    ComandoServerUnir(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje);

    Queue<std::shared_ptr<ComandoServer>>* ejecutar(GestorPartidas* gestor_partidas,
                                    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                    bool& cerrado,
                                    ServidorProtocolo& servidor_serializador) override;
};

#endif
