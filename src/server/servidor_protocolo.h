#ifndef SERVIDOR_PROTOCOLOO_H
#define SERVIDOR_PROTOCOLOO_H

#include <string>
#include <vector>

#include "../common/snapshot_dto.h"
#include "../common/socket.h"
#include "src/common/comando_crear_dto.h"
#include "src/common/comando_unir_dto.h"
#include "src/common/comando_validar_dto.h"

#include "partida.h"

class ServidorProtocolo {
private:
    Socket* socket;

    ComandoCrearDTO* deserializar_crear(bool* cerrado, int32_t& id_cliente);

    ComandoUnirDTO* deserializar_unir(bool* cerrado, const int32_t& id_cliente);

    ComandoValidarDTO* deserializar_validar(bool* cerrado, int32_t& id_cliente);

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

    ComandoDTO* obtener_comando(bool* cerrado, int32_t& id_cliente);
};

#endif
