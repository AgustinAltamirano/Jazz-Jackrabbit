#include "personaje_lori.h"

#include <utility>

PersonajeLori::PersonajeLori(const uint32_t id, SDL2pp::Renderer& renderer,
                             LectorTexturas& lector_texturas,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        Personaje(id, NOMBRE_PERSONAJE_LORI, renderer, lector_texturas, dimensiones_iniciales,
                  frames_por_sprite, frame_ticks_actuales) {
    mapa_estados_personaje.emplace(HIGHKICK, "highkick");

    ObjetoAnimado animacion_highkick(
            HIGHKICK, renderer, lector_texturas.obtener_textura_personaje(NOMBRE_PERSONAJE_LORI),
            lector_texturas.obtener_coords_personaje(NOMBRE_PERSONAJE_LORI,
                                                     mapa_estados_personaje.at(HIGHKICK)),
            dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);

    animaciones.emplace(HIGHKICK, std::move(animacion_highkick));
}

PersonajeLori::~PersonajeLori() = default;
