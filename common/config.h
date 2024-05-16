#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>

class ConfigAdmin {
private:
    std::unordered_map<std::string, int> configuracion;

public:
    ConfigAdmin(const ConfigAdmin &) = delete;

    ConfigAdmin &operator=(const ConfigAdmin &) = delete;

    ConfigAdmin();

    int get(const std::string &clave_config) const; // busca una clave en el map
};

#endif
