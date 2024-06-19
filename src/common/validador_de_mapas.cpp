#include "validador_de_mapas.h"

bool validador_de_mapas::validar_mapa_custom(const std::string& nombre) {
    return std::filesystem::exists(MAPAS_PATH + nombre + ".yaml");
}
