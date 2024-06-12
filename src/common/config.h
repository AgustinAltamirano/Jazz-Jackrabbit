#ifndef CONFIG_H
#define CONFIG_H

#include <mutex>
#include <string>
#include <unordered_map>

class ConfigAdmin {
private:
    ConfigAdmin();

    std::unordered_map<std::string, int> configuracion;

    static std::mutex m;

public:
    static ConfigAdmin& getInstance();

    ConfigAdmin(const ConfigAdmin&) = delete;

    ConfigAdmin operator=(const ConfigAdmin&) = delete;

    int get(const std::string& clave_config) const;  // busca una clave en el map
};

#endif
