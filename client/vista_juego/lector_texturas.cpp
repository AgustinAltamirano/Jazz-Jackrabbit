#include "lector_texturas.h"

#include <utility>

#include <yaml-cpp/yaml.h>

LectorTexturas::LectorTexturas(SDL2pp::Renderer& renderer): renderer(renderer) {}

void LectorTexturas::cargar_texturas_y_coordenadas() {
    const std::string ruta_personajes =
            std::string(ASSETS_PATH) + std::string(RUTA_SPRITES) + std::string(DIR_PERSONAJES);
    const std::string ruta_personajes_config = ruta_personajes + std::string(PERSONAJES_CONFIG);
    YAML::Node personajes = YAML::LoadFile(ruta_personajes_config);

    for (const auto& personaje: personajes["personajes"]) {
        auto nombre_personaje = personaje["nombre"].as<std::string>();
        auto imagen_personaje = ruta_personajes + personaje["imagen"].as<std::string>();
        SDL2pp::Texture textura(renderer, SDL2pp::Surface(imagen_personaje));
        std::unordered_map<std::string, std::vector<SDL2pp::Rect>> coords_personaje;
        texturas_personajes.emplace(nombre_personaje, std::move(textura));
        coords_personajes.emplace(nombre_personaje, std::move(coords_personaje));

        for (const auto& animacion: personaje["animaciones"]) {
            auto nombre_animacion = animacion["nombre"].as<std::string>();
            std::vector<SDL2pp::Rect> sprites;
            coords_personajes.at(nombre_personaje).emplace(nombre_animacion, std::move(sprites));

            for (const auto& sprite_coords: animacion["sprites"]) {
                SDL2pp::Rect sprite(sprite_coords["x"].as<int>(), sprite_coords["y"].as<int>(),
                                    sprite_coords["ancho"].as<int>(),
                                    sprite_coords["alto"].as<int>());
                coords_personajes.at(nombre_personaje).at(nombre_personaje).emplace_back(sprite);
            }
        }
    }
}
const SDL2pp::Texture& LectorTexturas::obtener_textura_personaje(const std::string& personaje) {
    return texturas_personajes.at(personaje);
}

const std::vector<SDL2pp::Rect>& LectorTexturas::obtener_coords_personaje(
        const std::string& personaje, const std::string& animacion) const {
    return coords_personajes.at(personaje).at(animacion);
}

LectorTexturas::~LectorTexturas() = default;
