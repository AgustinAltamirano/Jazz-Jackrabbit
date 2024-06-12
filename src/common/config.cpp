#include "config.h"

#include <yaml-cpp/yaml.h>

#include "constantes.h"

std::mutex ConfigAdmin::m;

ConfigAdmin& ConfigAdmin::getInstance() {
    std::lock_guard<std::mutex> lock(m);
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

    configuracion[VIDA_LAGARTO] = config[VIDA_LAGARTO].as<int>();
    configuracion[VIDA_MURCIELAGO] = config[VIDA_MURCIELAGO].as<int>();
    configuracion[VIDA_ESQUELETO] = config[VIDA_ESQUELETO].as<int>();

    configuracion[DANO_LAGARTO] = config[DANO_LAGARTO].as<int>();
    configuracion[DANO_MURCIELAGO] = config[DANO_MURCIELAGO].as<int>();
    configuracion[DANO_ESQUELETO] = config[DANO_ESQUELETO].as<int>();

    configuracion[VELOCIDAD_LAGARTO] = config[VELOCIDAD_LAGARTO].as<int>();
    configuracion[VELOCIDAD_MURCIELAGO] = config[VELOCIDAD_MURCIELAGO].as<int>();
    configuracion[VELOCIDAD_ESQUELETO] = config[VELOCIDAD_ESQUELETO].as<int>();

    configuracion[PUNTOS_LAGARTO] = config[PUNTOS_LAGARTO].as<int>();
    configuracion[PUNTOS_MURCIELAGO] = config[PUNTOS_MURCIELAGO].as<int>();
    configuracion[PUNTOS_ESQUELETO] = config[PUNTOS_ESQUELETO].as<int>();

    configuracion[FRAMES_REVIVIR_LAG] = config[FRAMES_REVIVIR_LAG].as<int>();
    configuracion[FRAMES_REVIVIR_MUR] = config[FRAMES_REVIVIR_MUR].as<int>();
    configuracion[FRAMES_REVIVIR_ESQ] = config[FRAMES_REVIVIR_ESQ].as<int>();

    configuracion[PROBABILIDAD_COM] = config[PROBABILIDAD_COM].as<int>();
    configuracion[PROBABILIDAD_MUN] = config[PROBABILIDAD_MUN].as<int>();
    configuracion[PROB_COM_BUENA] = config[PROB_COM_BUENA].as<int>();
    configuracion[PROB_COM_MALA] = config[PROB_COM_MALA].as<int>();
    configuracion[PROB_MUN_1] = config[PROB_MUN_1].as<int>();
    configuracion[PROB_MUN_2] = config[PROB_MUN_2].as<int>();
    configuracion[PROB_MUN_3] = config[PROB_MUN_3].as<int>();
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
