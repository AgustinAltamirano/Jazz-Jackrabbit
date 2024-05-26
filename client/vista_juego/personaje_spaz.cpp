#include "personaje_spaz.h"

#include <utility>

PersonajeSpaz::PersonajeSpaz(const uint32_t id, SDL2pp::Renderer& renderer,
                             LectorTexturas& lector_texturas,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        Personaje(id, NOMBRE_PERSONAJE_SPAZ, renderer, lector_texturas, dimensiones_iniciales,
                  frames_por_sprite, frame_ticks_actuales) {
    mapa_estados_personaje.emplace(CARGAR_SIDEKICK, "cargar_sidekick");
    mapa_estados_personaje.emplace(SIDEKICK, "sidekick");
    mapa_estados_personaje.emplace(PARAR_SIDEKICK, "parar_sidekick");

    ObjetoAnimado animacion_cargar_SIDEKICK(
            CARGAR_SIDEKICK, renderer,
            lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_SPAZ),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_SPAZ,
                                                     mapa_estados_personaje.at(CARGAR_SIDEKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
    ObjetoAnimado animacion_SIDEKICK(
            SIDEKICK, renderer, lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_SPAZ),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_SPAZ,
                                                     mapa_estados_personaje.at(SIDEKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
    ObjetoAnimado animacion_parar_SIDEKICK(
            PARAR_SIDEKICK, renderer,
            lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_SPAZ),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_SPAZ,
                                                     mapa_estados_personaje.at(PARAR_SIDEKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);

    animaciones.emplace(CARGAR_SIDEKICK, std::move(animacion_cargar_SIDEKICK));
    animaciones.emplace(SIDEKICK, std::move(animacion_SIDEKICK));
    animaciones.emplace(PARAR_SIDEKICK, std::move(animacion_parar_SIDEKICK));
}

PersonajeSpaz::~PersonajeSpaz() = default;
