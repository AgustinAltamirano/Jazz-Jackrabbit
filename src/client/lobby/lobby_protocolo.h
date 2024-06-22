#ifndef LOBBY_PROTOCOLO_H
#define LOBBY_PROTOCOLO_H

#include <memory>
#include <string>
#include <vector>

#include "../../common/socket_abstracto.h"
#include "../../common/tipo_escenario.h"
#include "../../common/tipo_personaje.h"

#include "comando_crear_dto.h"
#include "comando_dto.h"
#include "comando_unir_dto.h"
#include "comando_validar_dto.h"

class LobbyProtocolo {
private:
    SocketAbstracto* socket;

    std::shared_ptr<ComandoCrearDTO> deserializar_crear_partida(bool* cerrado);

    std::shared_ptr<ComandoUnirDTO> deserializar_unir_partida(bool* cerrado);

    std::shared_ptr<ComandoValidarDTO> deserializar_validar_escenario(bool* cerrado);

public:
    explicit LobbyProtocolo(SocketAbstracto* socket);

    std::shared_ptr<ComandoDTO> obtener_comando(bool* cerrado);

    int32_t obtener_id_cliente();

    void enviar_comando(const std::shared_ptr<ComandoDTO>& comando, bool* cerrado);
};

#endif
