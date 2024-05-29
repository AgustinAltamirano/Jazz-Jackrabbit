#ifndef SERVIDOR_DESERIALIZADOR_H
#define SERVIDOR_DESERIALIZADOR_H

#include "../common/comando_dto.h"
#include "../common/comando_crear_dto.h"
#include "../common/comando_unir_dto.h"
#include "../common/socket.h"
#include <string>
#include <vector>

class ServidorDeserializador {
private:
    Socket *socket;

    ComandoCrearDTO *deserializar_crear(bool *cerrado, int32_t &id_cliente);

    ComandoUnirDTO *deserializar_unir(bool *cerrado, int32_t &id_cliente);

    ComandoDTO *deserializar_comenzar(bool *cerrado, int32_t &id_cliente);

public:
    explicit ServidorDeserializador(Socket *socket);

    ComandoDTO *obtener_comando(bool *cerrado, int32_t &id_cliente);
};

#endif
