#include "config.h"
#include "constantes.h"

Config::Config() {
    YAML::Node config = YAML::LoadFile(ARCHIVO_CONFIG);

    configuracion["max_jugadores_por_partida"] = config["max_jugadores_por_partida"].as<int>();
    configuracion["max_partidas"] = config["max_partidas"].as<int>();
}

int Config::get(const std::string& clave) const {
    auto iterador = configuracion.find(clave);
    if (iterador != configuracion.end()) {
        return iterador->second;
    } else {
        throw std::invalid_argument("No se encontro la clave para el diccionario de configuracion. Tengo: " + clave);
    }
}
