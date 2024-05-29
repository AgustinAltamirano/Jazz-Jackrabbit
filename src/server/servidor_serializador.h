#ifndef SERVIDOR_SERIALIZADOR_H
#define SERVIDOR_SERIALIZADOR_H

#include "../common/snapshot_dto.h"
#include "../common/socket.h"
#include "./partida.h"

#include <vector>
#include <string>

class ServidorSerializador {
private:
    Socket *socket;

    std::vector<char> serializar_crear_partida(const int32_t &codigo_partida);

    std::vector<char> serializar_error_crear_partida();

    std::vector<char> serializar_unir_partida(const bool &unir);

    std::vector<char> serializar_iniciar_juego(const bool &iniciar);

    std::vector<char> serializar_id_cliente(const int32_t &id_cliente);

    std::vector<char> serializar_snapshot(SnapshotDTO snapshot_dto);

public:
    ServidorSerializador(); //Solo para testing

    explicit ServidorSerializador(Socket *socket);

    void enviar_iniciar_juego(const bool &iniciar, bool *cerrado);

    void enviar_crear_partida(const int32_t &codigo_partida, bool *cerrado);

    void enviar_error_crear_partida(bool *cerrado);

    void enviar_unir_partida(const bool &unir, bool *cerrado);

    void enviar_id_cliente(const int32_t &id_cliente, bool *cerrado);

    void enviar_snapshot(SnapshotDTO snapshot_dto, bool *cerrado);
};

#endif
