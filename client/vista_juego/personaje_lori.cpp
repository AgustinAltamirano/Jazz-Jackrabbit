#include "personaje_lori.h"

#include <utility>

PersonajeLori::PersonajeLori(const uint32_t id, SDL2pp::Renderer& renderer,
                             LectorTexturas& lector_texturas,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        Personaje(id, NOMBRE_PERSONAJE_LORI, renderer, lector_texturas, dimensiones_iniciales,
                  frames_por_sprite, frame_ticks_actuales) {
    mapa_estados_personaje.emplace(CARGAR_HIGHKICK, "cargar_highkick");
    mapa_estados_personaje.emplace(HIGHKICK, "highkick");
    mapa_estados_personaje.emplace(PARAR_HIGHKICK, "parar_highkick");

    ObjetoAnimado animacion_cargar_highkick(
            CARGAR_HIGHKICK, renderer,
            lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_LORI),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_LORI,
                                                     mapa_estados_personaje.at(CARGAR_HIGHKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
    ObjetoAnimado animacion_highkick(
            HIGHKICK, renderer, lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_LORI),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_LORI,
                                                     mapa_estados_personaje.at(HIGHKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
    ObjetoAnimado animacion_parar_highkick(
            PARAR_HIGHKICK, renderer,
            lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_LORI),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_LORI,
                                                     mapa_estados_personaje.at(PARAR_HIGHKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);

    animaciones.emplace(CARGAR_HIGHKICK, std::move(animacion_cargar_highkick));
    animaciones.emplace(HIGHKICK, std::move(animacion_highkick));
    animaciones.emplace(PARAR_HIGHKICK, std::move(animacion_parar_highkick));
}

PersonajeLori::~PersonajeLori() = default;
