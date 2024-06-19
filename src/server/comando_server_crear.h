#ifndef COMANDO_LOBBY_CREAR_H
#define COMANDO_LOBBY_CREAR_H

#include <string>

#include "../common/tipo_personaje.h"

#include "comando_server.h"


class ComandoServerCrear: public ComandoServer {
private:
    int32_t id_cliente;

    std::string nombre_escenario;

    int32_t codigo_partida;

    TipoPersonaje personaje;

    int8_t capacidad_partida{};

public:
    ComandoServerCrear(int32_t id_cliente, std::string nombre_escenario, TipoPersonaje personaje,
                    int8_t capacidad_partida);

    Queue<ComandoServer*>* ejecutar(GestorPartidas* gestor_partidas,
                                    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                    bool& cerrado,
                                    ServidorProtocolo& servidor_serializador) override;
};

#endif
