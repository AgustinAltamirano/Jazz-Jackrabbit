#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>

class Config {
private:
    std::unordered_map<std::string, int> configuracion;
public:

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    // pasaje por copia destruido

    Config();
    int get(const std::string& clave) const; // busca una clave en el map
};

#endif
