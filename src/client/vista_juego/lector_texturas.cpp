#include "lector_texturas.h"

#include <utility>

#include <SDL2/SDL_blendmode.h>
#include <yaml-cpp/yaml.h>

#include "vista_juego_exception.h"

LectorTexturas::LectorTexturas(SDL2pp::Renderer& renderer): renderer(renderer) {}

void LectorTexturas::cargar_texturas_y_coordenadas() {
    // Lectura de fondos de escenario y bloques
    const std::string ruta_escenarios(ASSETS_PATH RUTA_SPRITES DIR_ESCENARIOS);
    YAML::Node escenarios = YAML::LoadFile(ruta_escenarios + std::string(ESCENARIOS_CONFIG));

    for (const auto& escenario: escenarios["escenarios"]) {
        auto nombre_escenario = escenario["nombre"].as<std::string>();
        auto imagen_escenario = ruta_escenarios + escenario["imagen"].as<std::string>();

        SDL2pp::Surface surface(imagen_escenario);
        uint32_t color_key = SDL_MapRGB(surface.Get()->format, COLOR_KEY_ESCENARIOS_RED,
                                        COLOR_KEY_ESCENARIOS_GREEN, COLOR_KEY_ESCENARIOS_BLUE);
        surface.SetColorKey(true, color_key);
        SDL2pp::Texture textura(renderer, surface);
        textura.SetBlendMode(SDL_BLENDMODE_BLEND);
        texturas_escenarios.emplace(nombre_escenario, std::move(textura));
        auto coords = escenario["fondo_coords"][0];
        SDL2pp::Rect fondo_coords(coords["x"].as<int>(), coords["y"].as<int>(),
                                  coords["ancho"].as<int>(), coords["alto"].as<int>());
        coords_fondos_escenarios.emplace(nombre_escenario, fondo_coords);

        std::unordered_map<std::string, SDL2pp::Rect> dicc_coords;
        coords_bloques_escenarios.emplace(nombre_escenario, std::move(dicc_coords));

        for (const auto& bloque: escenario["bloques"]) {
            auto nombre_bloque = bloque["nombre"].as<std::string>();
            SDL2pp::Rect coords_bloque(bloque["x"].as<int>(), bloque["y"].as<int>(),
                                       bloque["ancho"].as<int>(), bloque["alto"].as<int>());
            coords_bloques_escenarios.at(nombre_escenario).emplace(nombre_bloque, coords_bloque);
        }
    }

    // Lectura de personajes
    const std::string ruta_personajes(ASSETS_PATH RUTA_SPRITES DIR_PERSONAJES);
    YAML::Node personajes = YAML::LoadFile(ruta_personajes + std::string(PERSONAJES_CONFIG));

    for (const auto& personaje: personajes["personajes"]) {
        auto nombre_personaje = personaje["nombre"].as<std::string>();
        auto imagen_personaje = ruta_personajes + personaje["imagen"].as<std::string>();

        SDL2pp::Surface surface(imagen_personaje);
        uint32_t color_key = SDL_MapRGB(surface.Get()->format, COLOR_KEY_PERSONAJES_RED,
                                        COLOR_KEY_PERSONAJES_GREEN, COLOR_KEY_PERSONAJES_BLUE);
        surface.SetColorKey(true, color_key);
        SDL2pp::Texture textura(renderer, surface);
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
                coords_personajes.at(nombre_personaje).at(nombre_animacion).emplace_back(sprite);
            }
        }
    }

    // Lectura de enemigos
    YAML::Node enemigos_config =
            YAML::LoadFile(ASSETS_PATH RUTA_SPRITES DIR_ENEMIGOS ENEMIGOS_CONFIG);
    auto imagen_enemigos = std::string(ASSETS_PATH RUTA_SPRITES DIR_ENEMIGOS) +
                           enemigos_config["imagen"].as<std::string>();
    SDL2pp::Surface surface_enemigos(imagen_enemigos);
    uint32_t color_key_enemigos = SDL_MapRGB(surface_enemigos.Get()->format, COLOR_KEY_ENEMIGOS_RED,
                                             COLOR_KEY_ENEMIGOS_GREEN, COLOR_KEY_ENEMIGOS_BLUE);
    surface_enemigos.SetColorKey(true, color_key_enemigos);
    textura_enemigos = std::make_unique<SDL2pp::Texture>(renderer, surface_enemigos);
    textura_enemigos->SetBlendMode(SDL_BLENDMODE_BLEND);

    for (const auto& enemigo: enemigos_config["enemigos"]) {
        auto nombre_enemigo = enemigo["nombre"].as<std::string>();
        std::vector<SDL2pp::Rect> sprites;
        coords_enemigos.emplace(nombre_enemigo, std::move(sprites));

        for (const auto& sprite_coords: enemigo["sprites"]) {
            SDL2pp::Rect sprite(sprite_coords["x"].as<int>(), sprite_coords["y"].as<int>(),
                                sprite_coords["ancho"].as<int>(), sprite_coords["alto"].as<int>());
            coords_enemigos.at(nombre_enemigo).emplace_back(sprite);
        }
    }

    // Lectura de fuente (números, símbolos, etc.)
    YAML::Node fuente_config = YAML::LoadFile(ASSETS_PATH RUTA_SPRITES DIR_FUENTE FUENTE_CONFIG);
    auto imagen_fuente = std::string(ASSETS_PATH RUTA_SPRITES DIR_FUENTE) +
                         fuente_config["imagen"].as<std::string>();
    SDL2pp::Surface surface_fuente(imagen_fuente);
    uint32_t color_key_fuente = SDL_MapRGB(surface_fuente.Get()->format, COLOR_KEY_ENEMIGOS_RED,
                                           COLOR_KEY_ENEMIGOS_GREEN, COLOR_KEY_ENEMIGOS_BLUE);
    surface_fuente.SetColorKey(true, color_key_fuente);
    textura_fuente = std::make_unique<SDL2pp::Texture>(renderer, surface_fuente);
    textura_fuente->SetBlendMode(SDL_BLENDMODE_BLEND);

    for (const auto& numero_coords: fuente_config["numeros"]) {
        SDL2pp::Rect sprite(numero_coords["x"].as<int>(), numero_coords["y"].as<int>(),
                            numero_coords["ancho"].as<int>(), numero_coords["alto"].as<int>());
        coords_numeros.emplace_back(sprite);
    }

    for (const auto& simbolo_coords: fuente_config["simbolos"]) {
        SDL2pp::Rect sprite(simbolo_coords["x"].as<int>(), simbolo_coords["y"].as<int>(),
                            simbolo_coords["ancho"].as<int>(), simbolo_coords["alto"].as<int>());
        coords_simbolos.emplace(simbolo_coords["nombre"].as<std::string>(), sprite);
    }

    // Lectura de íconos/ítems
    YAML::Node items_config = YAML::LoadFile(ASSETS_PATH RUTA_SPRITES DIR_ITEMS ITEMS_CONFIG);
    auto imagen_items = std::string(ASSETS_PATH RUTA_SPRITES DIR_ITEMS) +
                        items_config["imagen"].as<std::string>();
    SDL2pp::Surface surface_items(imagen_items);
    uint32_t color_key_items = SDL_MapRGB(surface_items.Get()->format, COLOR_KEY_ENEMIGOS_RED,
                                          COLOR_KEY_ENEMIGOS_GREEN, COLOR_KEY_ENEMIGOS_BLUE);
    surface_items.SetColorKey(true, color_key_items);
    textura_items = std::make_unique<SDL2pp::Texture>(renderer, surface_items);
    textura_items->SetBlendMode(SDL_BLENDMODE_BLEND);

    for (const auto& icono_coords: items_config["iconos"]) {
        SDL2pp::Rect sprite(icono_coords["x"].as<int>(), icono_coords["y"].as<int>(),
                            icono_coords["ancho"].as<int>(), icono_coords["alto"].as<int>());
        coords_iconos.emplace(icono_coords["nombre"].as<std::string>(), sprite);
    }

    for (const auto& arma_coords: items_config["armas"]) {
        SDL2pp::Rect sprite(arma_coords["x"].as<int>(), arma_coords["y"].as<int>(),
                            arma_coords["ancho"].as<int>(), arma_coords["alto"].as<int>());
        coords_armas.emplace(arma_coords["nombre"].as<std::string>(), sprite);
    }

    for (const auto& bala_coords: items_config["balas"]) {
        std::vector<SDL2pp::Rect> sprites_balas;
        coords_balas.emplace(bala_coords["nombre"].as<std::string>(), std::move(sprites_balas));
        SDL2pp::Rect sprite(bala_coords["x"].as<int>(), bala_coords["y"].as<int>(),
                            bala_coords["ancho"].as<int>(), bala_coords["alto"].as<int>());
        coords_balas.at(bala_coords["nombre"].as<std::string>()).emplace_back(sprite);
    }

    for (const auto& recogible_coords: items_config["recogibles"]) {
        std::vector<SDL2pp::Rect> sprites_recogibles;
        coords_balas.emplace(recogible_coords["nombre"].as<std::string>(),
                             std::move(sprites_recogibles));
        SDL2pp::Rect sprite(recogible_coords["x"].as<int>(), recogible_coords["y"].as<int>(),
                            recogible_coords["ancho"].as<int>(),
                            recogible_coords["alto"].as<int>());
        coords_balas.at(recogible_coords["nombre"].as<std::string>()).emplace_back(sprite);
    }
}

SDL2pp::Texture& LectorTexturas::obtener_textura_personaje(const std::string& personaje) {
    return texturas_personajes.at(personaje);
}

const std::vector<SDL2pp::Rect>& LectorTexturas::obtener_coords_personaje(
        const std::string& personaje, const std::string& animacion) const {
    return coords_personajes.at(personaje).at(animacion);
}

SDL2pp::Texture& LectorTexturas::obtener_textura_fondo_escenario(
        const std::string& tipo_escenario) {
    return texturas_escenarios.at(tipo_escenario);
}

const SDL2pp::Rect& LectorTexturas::obtener_coords_fondo_escenario(
        const std::string& tipo_escenario) const {
    return coords_fondos_escenarios.at(tipo_escenario);
}

SDL2pp::Texture& LectorTexturas::obtener_textura_bloque(const std::string& tipo_escenario) {
    return texturas_escenarios.at(tipo_escenario);
}

const SDL2pp::Rect& LectorTexturas::obtener_coords_bloque(const std::string& tipo_escenario,
                                                          const std::string& tipo_bloque) const {
    return coords_bloques_escenarios.at(tipo_escenario).at(tipo_bloque);
}

SDL2pp::Texture& LectorTexturas::obtener_textura_enemigos() const { return *textura_enemigos; }

const std::vector<SDL2pp::Rect>& LectorTexturas::obtener_coords_enemigo(
        const std::string& enemigo) const {
    return coords_enemigos.at(enemigo);
}
SDL2pp::Texture& LectorTexturas::obtener_textura_fuente() const { return *textura_fuente; }

const std::vector<SDL2pp::Rect>& LectorTexturas::obtener_coords_numeros() const {
    return coords_numeros;
}

const SDL2pp::Rect& LectorTexturas::obtener_coords_simbolo(
        const std::string& nombre_simbolo) const {
    return coords_simbolos.at(nombre_simbolo);
}


SDL2pp::Texture& LectorTexturas::obtener_textura_items() const { return *textura_items; }

const SDL2pp::Rect& LectorTexturas::obtener_coords_icono(const std::string& nombre_icono) const {
    return coords_iconos.at(nombre_icono);
}

const std::unordered_map<std::string, SDL2pp::Rect>& LectorTexturas::obtener_coords_armas() const {
    return coords_armas;
}

const std::vector<SDL2pp::Rect>& LectorTexturas::obtener_coords_bala(
        const std::string& nombre_arma) const {
    return coords_balas.at(nombre_arma);
}

const std::vector<SDL2pp::Rect>& LectorTexturas::obtener_coords_recogible(
        const std::string& nombre_recogible) const {
    return coords_recogibles.at(nombre_recogible);
}


LectorTexturas::IteradorTexturas LectorTexturas::begin_personajes() {
    const auto iterador_texturas = texturas_personajes.begin();
    return {texturas_personajes, coords_personajes, iterador_texturas,
            coords_personajes.at(iterador_texturas->first).begin()};
}

LectorTexturas::IteradorTexturas LectorTexturas::end_personajes() {
    // Se considera que IteradorTexturas se encuentra al final si su atributo iterador_texturas
    // se encuentra al final, sin importar el estado de iterador_animaciones.
    return {texturas_personajes, coords_personajes, texturas_personajes.end(),
            coords_personajes.at(texturas_personajes.begin()->first).begin()};
}

LectorTexturas::IteradorAnimaciones LectorTexturas::begin_animaciones_personaje(
        const std::string& nombre_personaje) {
    if (!coords_personajes.count(nombre_personaje)) {
        throw VistaJuegoException("Personaje no encontrado");
    }
    std::unordered_map<std::string, std::vector<SDL2pp::Rect>>& coords_per =
            coords_personajes.at(nombre_personaje);
    return {coords_per, coords_per.begin()};
}

LectorTexturas::IteradorAnimaciones LectorTexturas::end_animaciones_personaje(
        const std::string& nombre_personaje) {
    if (!coords_personajes.count(nombre_personaje)) {
        throw VistaJuegoException("Personaje no encontrado");
    }
    std::unordered_map<std::string, std::vector<SDL2pp::Rect>>& coords_per =
            coords_personajes.at(nombre_personaje);
    return {coords_per, coords_per.end()};
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


/** Iterador de animaciones de un solo objeto */

LectorTexturas::IteradorAnimaciones::IteradorAnimaciones(
        std::unordered_map<std::string, std::vector<SDL2pp::Rect>>& animaciones,
        std::unordered_map<std::string, std::vector<SDL2pp::Rect>>::const_iterator
                iterador_animaciones):
        coords(animaciones), iterador_animaciones(iterador_animaciones) {}

LectorTexturas::IteradorAnimaciones& LectorTexturas::IteradorAnimaciones::operator++() {
    ++iterador_animaciones;
    return *this;
}

bool LectorTexturas::IteradorAnimaciones::operator==(const IteradorAnimaciones& otro) const {
    return this->iterador_animaciones == otro.iterador_animaciones;
}

bool LectorTexturas::IteradorAnimaciones::operator!=(const IteradorAnimaciones& otro) const {
    return !(*this == otro);
}

const std::string& LectorTexturas::IteradorAnimaciones::obtener_nombre_animacion_actual() const {
    return iterador_animaciones->first;
}
const std::vector<SDL2pp::Rect>& LectorTexturas::IteradorAnimaciones::obtener_coordenadas_actuales()
        const {
    return iterador_animaciones->second;
}
