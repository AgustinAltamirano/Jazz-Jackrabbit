#ifndef VALIDADOR_DE_MAPAS_H
#define VALIDADOR_DE_MAPAS_H

#include <filesystem>
#include <string>

class validador_de_mapas {
public:
    static bool validar_mapa_custom(const std::string& nombre);
};

#endif  // VALIDADOR_DE_MAPAS_H
