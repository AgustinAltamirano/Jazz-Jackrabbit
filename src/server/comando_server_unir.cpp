#include "comando_server_unir.h"


ComandoServerUnir::ComandoServerUnir(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje):
        ComandoServer(id_cliente, UNIR),
        id_cliente(id_cliente),
        codigo_partida(codigo_partida),
        personaje(personaje) {}

Queue<std::shared_ptr<ComandoServer>>* ComandoServerUnir::ejecutar(
        GestorPartidas* gestor_partidas, Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
        bool& cerrado, ServidorProtocolo& servidor_serializador) {
    auto cola_recibidor = gestor_partidas->unir_partida(&cola_enviador, codigo_partida,
                                                   id_cliente, personaje);
    servidor_serializador.enviar_unir_partida((cola_recibidor != nullptr), &cerrado);
    return cola_recibidor;
}
