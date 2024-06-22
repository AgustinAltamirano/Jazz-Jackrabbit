#include "comando_server_validar.h"

#include <utility>

#include "../common/validador_de_mapas.h"

ComandoServerValidar::ComandoServerValidar(int32_t id_cliente, std::string nombre_escenario):
        ComandoServer(id_cliente, VALIDAR_ESCENARIO),
        nombre_escenario(std::move(nombre_escenario)) {}

Queue<std::shared_ptr<ComandoServer>>* ComandoServerValidar::ejecutar(
        GestorPartidas* gestor_partidas, Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
        bool& cerrado, ServidorProtocolo& servidor_serializador) {
    bool es_valido = validador_de_mapas::validar_mapa_custom(nombre_escenario);
    servidor_serializador.enviar_validar_escenario(es_valido, &cerrado);
    return nullptr;
}
