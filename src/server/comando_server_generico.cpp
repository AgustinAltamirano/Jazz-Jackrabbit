#include "comando_server_generico.h"

#include <iostream>

ComandoServerGenerico::ComandoServerGenerico(int32_t& id_cliente, TipoComando comando):
        ComandoServer(id_cliente, comando) {}

Queue<ComandoServer*>* ComandoServerGenerico::ejecutar(
        GestorPartidas* gestor_partidas, Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
        bool& cerrado, ServidorProtocolo& servidor_serializador) {
    return nullptr;
}
