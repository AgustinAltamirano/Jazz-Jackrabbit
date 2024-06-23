#include "comando_unir_dto.h"

#include <netinet/in.h>

ComandoUnirDTO::ComandoUnirDTO(int32_t id_cliente, int32_t codigo_partida, TipoPersonaje personaje):
        ComandoDTO(id_cliente, UNIR), codigo_partida(codigo_partida), personaje(personaje) {}

ComandoUnirDTO::ComandoUnirDTO(bool unio): ComandoDTO(UNIR), unio(unio), codigo_partida() {}

ComandoUnirDTO::ComandoUnirDTO(int32_t codigo_partida, TipoPersonaje personaje):
        ComandoDTO(UNIR), codigo_partida(codigo_partida), personaje(personaje) {}

int32_t ComandoUnirDTO::obtener_info() { return unio; }

std::vector<char> ComandoUnirDTO::serializar() {
    std::vector<char> buffer;
    buffer.push_back(UNIR);
    buffer.push_back(personaje);
    int32_t codigo_partida_transformado = htonl(codigo_partida);
    auto* p = reinterpret_cast<unsigned char const*>(&codigo_partida_transformado);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}
