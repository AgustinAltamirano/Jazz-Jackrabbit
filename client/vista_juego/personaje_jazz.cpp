#include "personaje_jazz.h"

#include <utility>

PersonajeJazz::PersonajeJazz(const uint32_t id, const std::string& nombre_personaje,
                             SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        Personaje(id, nombre_personaje, renderer, lector_texturas, dimensiones_iniciales,
                  frames_por_sprite, frame_ticks_actuales) {
    mapa_estados_personaje.emplace(CARGAR_UPPERCUT, "cargar_uppercut");
    mapa_estados_personaje.emplace(UPPERCUT, "uppercut");
    mapa_estados_personaje.emplace(PARAR_UPPERCUT, "parar_uppercut");

    ObjetoAnimado animacion_cargar_uppercut(
            CARGAR_UPPERCUT, renderer, lector_texturas.obtener_textura_personaje(nombre_personaje),
            lector_texturas.obtener_coords_personaje(nombre_personaje,
                                                     mapa_estados_personaje.at(CARGAR_UPPERCUT)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
    ObjetoAnimado animacion_uppercut(
            UPPERCUT, renderer, lector_texturas.obtener_textura_personaje(nombre_personaje),
            lector_texturas.obtener_coords_personaje(nombre_personaje,
                                                     mapa_estados_personaje.at(UPPERCUT)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
    ObjetoAnimado animacion_parar_uppercut(
            PARAR_UPPERCUT, renderer, lector_texturas.obtener_textura_personaje(nombre_personaje),
            lector_texturas.obtener_coords_personaje(nombre_personaje,
                                                     mapa_estados_personaje.at(PARAR_UPPERCUT)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);

    animaciones.emplace(CARGAR_UPPERCUT, std::move(animacion_cargar_uppercut));
    animaciones.emplace(UPPERCUT, std::move(animacion_uppercut));
    animaciones.emplace(PARAR_UPPERCUT, std::move(animacion_parar_uppercut));
}

PersonajeJazz::~PersonajeJazz() = default;
