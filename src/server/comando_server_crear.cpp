#include "comando_server_crear.h"

#include <utility>

ComandoServerCrear::ComandoServerCrear(int32_t id_cliente, std::string nombre_escenario,
                                 TipoPersonaje personaje, int8_t capacidad_partida):
        ComandoServer(id_cliente, CREAR),
        id_cliente(id_cliente),
        nombre_escenario(std::move(nombre_escenario)),
        personaje(personaje),
        capacidad_partida(capacidad_partida),
        codigo_partida() {}

Queue<ComandoServer*>* ComandoServerCrear::ejecutar(
        GestorPartidas* gestor_partidas, Queue<std::shared_ptr<SnapshotDTO>>& cola_enviador,
        bool& cerrado, ServidorProtocolo& servidor_serializador) {
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
