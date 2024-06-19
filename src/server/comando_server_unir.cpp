#include "comando_server_unir.h"


ComandoLobbyUnir::ComandoLobbyUnir(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje):
        ComandoServer(id_cliente, UNIR),
        codigo_partida(codigo_partida),
        personaje(personaje),
        unio() {}

ComandoLobbyUnir::ComandoLobbyUnir(bool unio):
        ComandoServer(UNIR),
        unio(unio),
        codigo_partida(),
        personaje() {}

int32_t ComandoLobbyUnir::obtener_codigo_partida() const { return codigo_partida; }

bool ComandoLobbyUnir::obtener_unio() const { return unio; }

Queue<ComandoServer*>* ComandoLobbyUnir::ejecutar(GestorPartidas* gestor_partidas,
                              Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                              int32_t id_cliente, bool& cerrado,
                              ServidorProtocolo& servidor_serializador) {
    auto cola_recibidor = gestor_partidas->unir_partida(&cola_enviador, codigo_partida,
                                                   id_cliente, personaje);
    servidor_serializador.enviar_unir_partida((cola_recibidor != nullptr), &cerrado);
    return cola_recibidor;
}
