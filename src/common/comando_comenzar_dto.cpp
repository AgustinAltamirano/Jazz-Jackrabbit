#include "comando_comenzar_dto.h"

ComandoComenzarDTO::ComandoComenzarDTO() : ComandoDTO(COMENZAR), empezo(false) {}

ComandoComenzarDTO::ComandoComenzarDTO(bool unio) : ComandoDTO(COMENZAR), empezo(unio) {}

bool ComandoComenzarDTO::obtener_empezo() { return empezo; }
