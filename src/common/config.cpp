#include "config.h"

#include <yaml-cpp/yaml.h>

#include "constantes.h"

ConfigAdmin& ConfigAdmin::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    static ConfigAdmin singleton;
    return singleton;
}

ConfigAdmin::ConfigAdmin() {
    YAML::Node config = YAML::LoadFile(ARCHIVO_CONFIG);

    configuracion[MAX_JUG_POR_PARTIDA] = config[MAX_JUG_POR_PARTIDA].as<int>();
    configuracion[MAX_PARTIDAS] = config[MAX_PARTIDAS].as<int>();

    configuracion[VIDA_INICIAL] = config[VIDA_INICIAL].as<int>();
    configuracion[GRAVEDAD] = config[GRAVEDAD].as<int>();

    configuracion[VEL_ARMA_INF] = config[VEL_ARMA_INF].as<int>();
    configuracion[DANO_ARMA_INF] = config[DANO_ARMA_INF].as<int>();
    configuracion[FRAMES_REC_ARMA_INF] = config[FRAMES_REC_ARMA_INF].as<int>();

    configuracion[VEL_ARMA1] = config[VEL_ARMA1].as<int>();
    configuracion[DANO_ARMA1] = config[DANO_ARMA1].as<int>();
    configuracion[FRAMES_REC_ARMA1] = config[FRAMES_REC_ARMA1].as<int>();

    configuracion[VEL_ARMA2] = config[VEL_ARMA2].as<int>();
    configuracion[CAIDA_ARMA2] = config[CAIDA_ARMA2].as<int>();
    configuracion[DANO_ARMA2] = config[DANO_ARMA2].as<int>();
    configuracion[FRAMES_REC_ARMA2] = config[FRAMES_REC_ARMA2].as<int>();

    configuracion[VEL_ARMA3] = config[VEL_ARMA3].as<int>();
    configuracion[DANO_ARMA3] = config[DANO_ARMA3].as<int>();
    configuracion[FRAMES_REC_ARMA3] = config[FRAMES_REC_ARMA3].as<int>();
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
