#ifndef SERVIDOR_DESERIALIZADOR_H
#define SERVIDOR_DESERIALIZADOR_H

#include <string>
#include <vector>

#include "../common/comando_crear_dto.h"
#include "../common/comando_dto.h"
#include "../common/comando_unir_dto.h"
#include "../common/socket.h"

class ServidorDeserializador {
private:
    Socket* socket;

    ComandoCrearDTO* deserializar_crear(bool* cerrado, int32_t& id_cliente);

    ComandoUnirDTO* deserializar_unir(bool* cerrado, const int32_t& id_cliente);

public:
    explicit ServidorDeserializador(Socket* socket);

    ComandoDTO* obtener_comando(bool* cerrado, int32_t& id_cliente);
};

#endif
