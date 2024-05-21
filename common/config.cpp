#include "config.h"
#include "constantes.h"

ConfigAdmin& ConfigAdmin::getInstance() {
    static ConfigAdmin singleton;
    return singleton;
}

ConfigAdmin::ConfigAdmin() {
    YAML::Node config = YAML::LoadFile(ARCHIVO_CONFIG);

    configuracion[MAX_JUG_POR_PARTIDA] = config[MAX_JUG_POR_PARTIDA].as<int>();
    configuracion[MAX_PARTIDAS] = config[MAX_PARTIDAS].as<int>();
}

int ConfigAdmin::get(const std::string& clave_config) const {
    auto iterador = configuracion.find(clave_config);
    if (iterador != configuracion.end()) {
        return iterador->second;
    } else {
        throw std::invalid_argument(
                "No se encontro la clave para el diccionario de configuracion. Tengo: " +
                clave_config);
    }
}
