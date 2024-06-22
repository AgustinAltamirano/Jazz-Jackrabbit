#include "comando_validar_dto.h"

ComandoValidarDTO::ComandoValidarDTO(int32_t& id_cliente, std::string nombre_escenario):
        ComandoDTO(id_cliente, VALIDAR_ESCENARIO), nombre_escenario(nombre_escenario) {}

ComandoValidarDTO::ComandoValidarDTO(bool es_valida):
        ComandoDTO(VALIDAR_ESCENARIO), es_valida(es_valida) {}

ComandoValidarDTO::ComandoValidarDTO(std::string nombre_escenario):
        ComandoDTO(VALIDAR_ESCENARIO), nombre_escenario(nombre_escenario) {}

int32_t ComandoValidarDTO::obtener_info() { return es_valida; }

std::vector<char> ComandoValidarDTO::serializar() {
    std::vector<char> buffer;
    uint8_t len_nombre = nombre_escenario.length();
    buffer.push_back(VALIDAR_ESCENARIO);
    buffer.push_back(len_nombre);
    buffer.insert(buffer.end(), nombre_escenario.begin(), nombre_escenario.end());
    return buffer;
}
