#ifndef LOBBY_PROTOCOLO_H
#define LOBBY_PROTOCOLO_H

#include <string>
#include <vector>

#include "../../common/tipo_escenario.h"
#include "../../common/tipo_personaje.h"
#include "src/common/comando_crear_dto.h"
#include "src/common/comando_dto.h"
#include "src/common/comando_unir_dto.h"
#include "src/common/comando_validar_dto.h"
#include "src/common/socket.h"

class LobbyProtocolo {
private:
    Socket* socket;

public:
    explicit LobbyProtocolo(Socket* socket);

    std::vector<char> serializar_crear_partida(const std::string& nombre_escenario,
                                               const TipoPersonaje& personaje,
                                               const int8_t& capacidad_partida);

    std::vector<char> serializar_unir_partida(const int32_t& codigo_partida,
                                              const TipoPersonaje& personaje);

    std::vector<char> serializar_validar_escenario(const std::string& nombre_escenario);

    ComandoDTO* obtener_comando(bool* cerrado);

    int32_t obtener_id_cliente();

    ComandoCrearDTO* deserializar_crear_partida(bool* cerrado);

    ComandoUnirDTO* deserializar_unir_partida(bool* cerrado);

    ComandoValidarDTO* deserializar_validar_escenario(bool* cerrado);

    void enviar_comando(std::vector<char> bytes, bool* cerrado);
};

#endif
