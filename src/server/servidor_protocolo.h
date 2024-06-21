#ifndef SERVIDOR_PROTOCOLO_H
#define SERVIDOR_PROTOCOLO_H

#include <string>
#include <vector>

#include "../common/snapshot_dto.h"
#include "../common/socket.h"

#include "partida.h"
#include "servidor_protocolo_serializador.h"

#define TAM_TIPO_COMANDO 1
class ComandoServerCrear;
class ComandoServerUnir;
class ComandoServerValidar;


class ServidorProtocolo {
private:
    SocketAbstracto* socket;

    ServidorProtocoloSerializador serializador;

    std::unique_ptr<ComandoServerCrear> deserializar_crear(bool* cerrado, int32_t& id_cliente);

    std::unique_ptr<ComandoServerUnir> deserializar_unir(bool* cerrado, const int32_t& id_cliente);

    std::unique_ptr<ComandoServerValidar> deserializar_validar(bool* cerrado, int32_t& id_cliente);

public:
    explicit ServidorProtocolo(SocketAbstracto* socket);

    ServidorProtocolo();

    void enviar_crear_partida(const int32_t& codigo_partida, bool* cerrado);

    void enviar_error_crear_partida(bool* cerrado);

    void enviar_unir_partida(const bool& unir, bool* cerrado);

    void enviar_id_cliente(const int32_t& id_cliente, bool* cerrado);

    void enviar_snapshot(std::shared_ptr<SnapshotDTO>& snapshot_dto, bool* cerrado);

    void enviar_validar_escenario(const bool& es_valido, bool* cerrado);

    std::unique_ptr<ComandoServer> obtener_comando(bool* cerrado, int32_t& id_cliente);
};

#endif
