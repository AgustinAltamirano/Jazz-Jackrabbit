#include "comando_server_crear.h"

#include <utility>

ComandoLobbyCrear::ComandoLobbyCrear(int32_t& id_cliente, std::string nombre_escenario,
                                 TipoPersonaje personaje, int8_t capacidad_partida):
        ComandoServer(id_cliente, CREAR),
        nombre_escenario(std::move(nombre_escenario)),
        personaje(personaje),
        capacidad_partida(capacidad_partida),
        codigo_partida() {}

ComandoLobbyCrear::ComandoLobbyCrear(int32_t codigo_partida):
        ComandoServer(CREAR), codigo_partida(codigo_partida), personaje() {}

int32_t ComandoLobbyCrear::obtener_codigo_partida() const { return codigo_partida; }

Queue<ComandoServer*>* ComandoLobbyCrear::ejecutar(GestorPartidas* gestor_partidas,
                               Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
                               int32_t id_cliente, bool& cerrado, ServidorProtocolo& servidor_serializador) {
    auto cola_recibidor =
            gestor_partidas->crear_partida(&cola_enviador, nombre_escenario, id_cliente,
                                           codigo_partida, personaje, capacidad_partida);
    // Si me devuelve un puntero nulo significa que no se pudo crear la partida
    if (cola_recibidor == nullptr) {
        servidor_serializador.enviar_error_crear_partida(&cerrado);
    } else {
        servidor_serializador.enviar_crear_partida(codigo_partida, &cerrado);
    }
    return cola_recibidor;
}
