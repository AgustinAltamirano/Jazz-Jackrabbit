#include "comando_validar_dto.h"

ComandoValidarDTO::ComandoValidarDTO(int32_t& id_cliente, std::string nombre_escenario):
        ComandoDTO(id_cliente, VALIDAR_ESCENARIO), nombre_escenario(nombre_escenario) {}

ComandoValidarDTO::ComandoValidarDTO(bool es_valida):
        ComandoDTO(VALIDAR_ESCENARIO), es_valida(es_valida) {}

std::string ComandoValidarDTO::obtener_nombre_escenario() { return nombre_escenario; }

bool ComandoValidarDTO::obtener_es_valida() { return es_valida; }
