#include "comando_crear_dto.h"

ComandoCrearDTO::ComandoCrearDTO(int32_t& id_cliente, std::string nombre_escenario,
                                 TipoPersonaje personaje, int8_t capacidad_partida):
        ComandoDTO(id_cliente, CREAR),
        nombre_escenario(nombre_escenario),
        personaje(personaje),
        capacidad_partida(capacidad_partida),
        codigo_partida() {}

ComandoCrearDTO::ComandoCrearDTO(int32_t codigo_partida):
        ComandoDTO(CREAR), codigo_partida(codigo_partida) {}

ComandoCrearDTO::ComandoCrearDTO(std::string nombre_escenario, TipoPersonaje personaje,
                                 int8_t capacidad_partida):
        ComandoDTO(CREAR),
        nombre_escenario(nombre_escenario),
        personaje(personaje),
        capacidad_partida(capacidad_partida),
        codigo_partida() {}

int32_t ComandoCrearDTO::obtener_info() { return codigo_partida; }

std::vector<char> ComandoCrearDTO::serializar() {
    std::vector<char> buffer;
    uint8_t len_nombre = nombre_escenario.length();
    buffer.push_back(CREAR);
    buffer.push_back(len_nombre);
    buffer.insert(buffer.end(), nombre_escenario.begin(), nombre_escenario.end());
    buffer.push_back(personaje);
    buffer.push_back(capacidad_partida);
    return buffer;
}
