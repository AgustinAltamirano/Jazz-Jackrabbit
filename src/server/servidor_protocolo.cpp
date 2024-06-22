#include "servidor_protocolo.h"

#include <memory>

#include <arpa/inet.h>

#include "comando_server_crear.h"
#include "comando_server_generico.h"
#include "comando_server_unir.h"
#include "comando_server_validar.h"

ServidorProtocolo::ServidorProtocolo(SocketAbstracto* socket): socket(socket) {}

void ServidorProtocolo::enviar_crear_partida(const int32_t& codigo_partida, bool* cerrado) {
    std::vector<char> buffer = serializador.serializar_crear_partida(codigo_partida);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorProtocolo::enviar_error_crear_partida(bool* cerrado) {
    std::vector<char> buffer = serializador.serializar_error_crear_partida();
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorProtocolo::enviar_unir_partida(const bool& unir, bool* cerrado) {
    std::vector<char> buffer = serializador.serializar_unir_partida(unir);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorProtocolo::enviar_id_cliente(const int32_t& id_cliente, bool* cerrado) {
    std::vector<char> buffer = serializador.serializar_id_cliente(id_cliente);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorProtocolo::enviar_validar_escenario(const bool& es_valido, bool* cerrado) {
    std::vector<char> buffer = serializador.serializar_validar_escenario(es_valido);
    socket->sendall(buffer.data(), buffer.size(), cerrado);
}

void ServidorProtocolo::enviar_snapshot(std::shared_ptr<SnapshotDTO>& snapshot_dto, bool* cerrado) {
    std::vector<ClienteDTO>& clientes_dto = snapshot_dto->obtener_clientes();
    std::vector<BloqueEscenarioDTO>& bloques_dto = snapshot_dto->obtener_bloques_escenario();
    std::vector<BalaDTO>& balas_dto = snapshot_dto->obtener_balas();
    std::vector<EnemigoDTO>& enemigos_dto = snapshot_dto->obtener_enemigos();
    std::vector<RecogibleDTO>& recogibles_dto = snapshot_dto->obtener_recogibles();

    const uint32_t num_clientes = htonl(clientes_dto.size());
    const uint32_t num_bloques = htonl(bloques_dto.size());
    const uint32_t num_balas = htonl(balas_dto.size());
    const uint32_t num_enemigos = htonl(enemigos_dto.size());
    const uint32_t num_recogibles = htonl(recogibles_dto.size());

    const auto tipo_escenario = static_cast<uint8_t>(snapshot_dto->obtener_tipo_escenario());
    const int32_t tiempo_restante = htonl(snapshot_dto->obtener_tiempo_restante());
    const auto fin_juego = snapshot_dto->es_fin_juego();
    const auto hubo_disparo = snapshot_dto->obtener_hubo_disparo();
    const auto alguien_fue_herido = snapshot_dto->obtener_hubo_herido();
    const auto alguien_murio = snapshot_dto->obtener_hubo_muerte();

    socket->sendall(&num_clientes, sizeof(num_clientes), cerrado);
    socket->sendall(&num_bloques, sizeof(num_bloques), cerrado);
    socket->sendall(&num_balas, sizeof(num_balas), cerrado);
    socket->sendall(&num_enemigos, sizeof(num_enemigos), cerrado);
    socket->sendall(&num_recogibles, sizeof(num_recogibles), cerrado);
    socket->sendall(&tipo_escenario, sizeof(tipo_escenario), cerrado);
    socket->sendall(&tiempo_restante, sizeof(tiempo_restante), cerrado);
    socket->sendall(&fin_juego, sizeof(fin_juego), cerrado);
    socket->sendall(&hubo_disparo, sizeof(hubo_disparo), cerrado);
    socket->sendall(&alguien_fue_herido, sizeof(alguien_fue_herido), cerrado);
    socket->sendall(&alguien_murio, sizeof(alguien_murio), cerrado);

    for (const auto& cliente_dto: clientes_dto) {
        socket->sendall(&cliente_dto, sizeof(cliente_dto), cerrado);
    }

    for (const auto& bloque_dto: bloques_dto) {
        socket->sendall(&bloque_dto, sizeof(bloque_dto), cerrado);
    }

    for (const auto& bala_dto: balas_dto) {
        socket->sendall(&bala_dto, sizeof(bala_dto), cerrado);
    }

    for (const auto& enemigo_dto: enemigos_dto) {
        socket->sendall(&enemigo_dto, sizeof(enemigo_dto), cerrado);
    }

    for (const auto& recogible_dto: recogibles_dto) {
        socket->sendall(&recogible_dto, sizeof(recogible_dto), cerrado);
    }
}

std::shared_ptr<ComandoServer> ServidorProtocolo::obtener_comando(bool* cerrado,
                                                                  int32_t& id_cliente) {
    char code = 0;
    socket->recvall(&code, TAM_TIPO_COMANDO, cerrado);
    if (*cerrado) {
        throw std::runtime_error("Se cerro el socket esperando una instruccion");
    }
    TipoComando comando = static_cast<TipoComando>(code);
    switch (comando) {
        case CREAR:
            return deserializar_crear(cerrado, id_cliente);
        case UNIR:
            return deserializar_unir(cerrado, id_cliente);
        case VALIDAR_ESCENARIO:
            return deserializar_validar(cerrado, id_cliente);
        default:
            return std::make_shared<ComandoServerGenerico>(id_cliente, comando);
    }
}

std::shared_ptr<ComandoServerCrear> ServidorProtocolo::deserializar_crear(bool* cerrado,
                                                                          int32_t& id_cliente) {
    uint8_t len_nombre = 0;
    socket->recvall(&len_nombre, 1, cerrado);
    std::vector<char> buffer(len_nombre);
    socket->recvall(buffer.data(), len_nombre, cerrado);
    TipoPersonaje personaje;
    int8_t capacidad_partida;
    socket->recvall(&personaje, 1, cerrado);
    socket->recvall(&capacidad_partida, 1, cerrado);

    auto crear_dto = std::make_shared<ComandoServerCrear>(
            id_cliente, std::string(buffer.begin(), buffer.end()), personaje, capacidad_partida);

    return crear_dto;
}

std::shared_ptr<ComandoServerUnir> ServidorProtocolo::deserializar_unir(bool* cerrado,
                                                                        const int32_t& id_cliente) {
    TipoPersonaje personaje;
    socket->recvall(&personaje, 1, cerrado);
    int32_t codigo_partida;
    socket->recvall(&codigo_partida, sizeof(int32_t), cerrado);
    codigo_partida = ntohl(codigo_partida);

    auto unir_dto = std::make_shared<ComandoServerUnir>(id_cliente, codigo_partida, personaje);

    return unir_dto;
}

std::shared_ptr<ComandoServerValidar> ServidorProtocolo::deserializar_validar(bool* cerrado,
                                                                              int32_t& id_cliente) {
    uint8_t len_nombre = 0;
    socket->recvall(&len_nombre, 1, cerrado);
    std::vector<char> buffer(len_nombre);
    socket->recvall(buffer.data(), len_nombre, cerrado);

    auto validar_dto = std::make_shared<ComandoServerValidar>(
            id_cliente, std::string(buffer.begin(), buffer.end()));

    return validar_dto;
}
