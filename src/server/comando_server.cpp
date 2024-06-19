#include "comando_server.h"

#include <iostream>

ComandoServer::ComandoServer() {
    id_cliente = -1;
    comando = NINGUNA;
}

ComandoServer::ComandoServer(TipoComando comando): comando(comando) { id_cliente = -1; }

ComandoServer::ComandoServer(int32_t& id_cliente, TipoComando comando):
        id_cliente(id_cliente), comando(comando) {}

TipoComando ComandoServer::obtener_comando() { return comando; }

int32_t ComandoServer::obtener_id_cliente() { return id_cliente; }

Queue<ComandoServer*>* ComandoServer::ejecutar(GestorPartidas* gestor_partidas,
                                             Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                                             int32_t id_cliente, bool& cerrado,
                                             ServidorProtocolo& servidor_serializador) {
    return nullptr;
}
