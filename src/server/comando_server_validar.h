#ifndef COMANDO_LOBBY_VALIDAR_H
#define COMANDO_LOBBY_VALIDAR_H

#include <string>

#include "../common/tipo_personaje.h"

#include "comando_server.h"


class ComandoServerValidar: public ComandoServer {
private:
    std::string nombre_escenario;

public:
    ComandoServerValidar(int32_t id_cliente, std::string nombre_escenario);

    Queue<std::shared_ptr<ComandoServer>>* ejecutar(GestorPartidas* gestor_partidas,
                                    Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                    bool& cerrado,
                                    ServidorProtocolo& servidor_serializador) override;
};

#endif
