#include "lector_texturas.h"

#include <utility>

#include <SDL2/SDL_blendmode.h>
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
        SDL2pp::Texture textura(renderer, SDL2pp::Surface(imagen_personaje).SetColorKey(true, 0));
        textura.SetBlendMode(SDL_BLENDMODE_BLEND);
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

LectorTexturas::IteradorTexturas LectorTexturas::beginPersonajes() {
    const auto iterador_texturas = texturas_personajes.begin();
    return {texturas_personajes, coords_personajes, iterador_texturas,
            coords_personajes.at(iterador_texturas->first).begin()};
}

LectorTexturas::IteradorTexturas LectorTexturas::endPersonajes() {
    // Se considera que IteradorTexturas se encuentra al final si su atributo iterador_texturas
    // se encuentra al final, sin importar el estado de iterador_animaciones.
    return {texturas_personajes, coords_personajes, texturas_personajes.end(),
            coords_personajes.at(texturas_personajes.begin()->first).begin()};
}

LectorTexturas::~LectorTexturas() = default;


/** Iterador del LectorTexturas */

LectorTexturas::IteradorTexturas::IteradorTexturas(
        std::unordered_map<std::string, SDL2pp::Texture>& texturas,
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<SDL2pp::Rect>>>&
                coords,
        const std::unordered_map<std::string, SDL2pp::Texture>::iterator iterador_texturas,
        const std::unordered_map<std::string, std::vector<SDL2pp::Rect>>::const_iterator
                iterador_animaciones):
        texturas(texturas),
        coords(coords),
        iterador_texturas(iterador_texturas),
        iterador_animaciones(iterador_animaciones) {}

LectorTexturas::IteradorTexturas& LectorTexturas::IteradorTexturas::operator++() {
    // Se pasa a la siguiente animación
    ++iterador_animaciones;

    // Si todavía quedan animaciones por recorrer, el iterador ya se encuentra en el estado deseado
    if (iterador_animaciones != coords.at(iterador_texturas->first).end()) {
        return *this;
    }

    // Caso contrario, se pasa a la siguiente textura
    ++iterador_texturas;

    // Si quedan texturas por recorrer, se selecciona la primera animación
    // de la nueva textura actual.
    if (iterador_texturas != texturas.end()) {
        iterador_animaciones = coords.at(iterador_texturas->first).begin();
    }

    // Llegado este punto, el iterador ya se encuentra en el estado deseado
    return *this;
}

bool LectorTexturas::IteradorTexturas::operator==(const IteradorTexturas& otro) const {
    // Se considera que IteradorTexturas se encuentra al final si su atributo iterador_texturas
    // se encuentra al final, sin importar el estado de iterador_animaciones.
    if (this->iterador_texturas == this->texturas.end() &&
        otro.iterador_texturas == otro.texturas.end()) {
        // Ambas instancias de IteradorTexturas se encuentran al final. Por lo tanto, son iguales.
        return true;
    }
    return this->iterador_texturas == otro.iterador_texturas &&
           this->iterador_animaciones == otro.iterador_animaciones;
}

bool LectorTexturas::IteradorTexturas::operator!=(const IteradorTexturas& otro) const {
    return !(*this == otro);
}

const std::string& LectorTexturas::IteradorTexturas::obtener_nombre_objeto_actual() const {
    return iterador_texturas->first;
}

SDL2pp::Texture& LectorTexturas::IteradorTexturas::obtener_textura_actual() const {
    return iterador_texturas->second;
}

const std::string& LectorTexturas::IteradorTexturas::obtener_nombre_animacion_actual() const {
    return iterador_animaciones->first;
}

const std::vector<SDL2pp::Rect>& LectorTexturas::IteradorTexturas::obtener_coordenadas_actuales()
        const {
    return iterador_animaciones->second;
}
