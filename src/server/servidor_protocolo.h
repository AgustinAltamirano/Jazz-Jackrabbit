#ifndef SERVIDOR_PROTOCOLOO_H
#define SERVIDOR_PROTOCOLOO_H

#include <string>
#include <vector>

#include "../common/snapshot_dto.h"
#include "../common/socket.h"
#include "partida.h"

#define TAM_TIPO_COMANDO 1
class ComandoLobbyCrear;
class ComandoLobbyUnir;
class ComandoLobbyValidar;


class ServidorProtocolo {
private:
    Socket* socket;

    std::unique_ptr<ComandoLobbyCrear> deserializar_crear(bool* cerrado, int32_t& id_cliente);

    std::unique_ptr<ComandoLobbyUnir> deserializar_unir(bool* cerrado, const int32_t& id_cliente);

    std::unique_ptr<ComandoLobbyValidar> deserializar_validar(bool* cerrado, int32_t& id_cliente);

public:
    ServidorProtocolo();  // Solo para testing

    explicit ServidorProtocolo(Socket* socket);

    void enviar_crear_partida(const int32_t& codigo_partida, bool* cerrado);

    void enviar_error_crear_partida(bool* cerrado);

    void enviar_unir_partida(const bool& unir, bool* cerrado);

    void enviar_id_cliente(const int32_t& id_cliente, bool* cerrado);

    void enviar_snapshot(std::shared_ptr<SnapshotDTO>& snapshot_dto, bool* cerrado);

    void enviar_validar_escenario(const bool& es_valido, bool* cerrado);

    /** serializadores publicos para testing **/

    std::vector<char> serializar_crear_partida(const int32_t& codigo_partida);

    std::vector<char> serializar_error_crear_partida();

    std::vector<char> serializar_unir_partida(const bool& unir);

    std::vector<char> serializar_validar_escenario(const bool& es_valido);

    std::vector<char> serializar_id_cliente(const int32_t& id_cliente);

    std::unique_ptr<ComandoServer> obtener_comando(bool* cerrado, int32_t& id_cliente);
};

#endif
