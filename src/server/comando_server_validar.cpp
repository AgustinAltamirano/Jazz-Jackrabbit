#include "comando_server_validar.h"

#include <utility>

#include "../common/validador_de_mapas.h"

ComandoLobbyValidar::ComandoLobbyValidar(int32_t& id_cliente, std::string nombre_escenario):
        ComandoServer(id_cliente, VALIDAR_ESCENARIO),
        nombre_escenario(std::move(nombre_escenario)),
        es_valida() {}

ComandoLobbyValidar::ComandoLobbyValidar(bool es_valida):
        ComandoServer(VALIDAR_ESCENARIO), es_valida(es_valida) {}

std::string ComandoLobbyValidar::obtener_nombre_escenario() { return nombre_escenario; }

bool ComandoLobbyValidar::obtener_es_valida() const { return es_valida; }

Queue<ComandoServer*>* ComandoLobbyValidar::ejecutar(
        GestorPartidas* gestor_partidas, Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
        int32_t id_cliente, bool& cerrado, ServidorProtocolo& servidor_serializador) {
    bool es_valido = validador_de_mapas::validar_mapa_custom(nombre_escenario);
    servidor_serializador.enviar_validar_escenario(es_valido, &cerrado);
    return nullptr;
}
