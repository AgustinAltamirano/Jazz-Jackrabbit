#include "admin_explosiones.h"

#include <unordered_set>
#include <utility>
#include <vector>

SDL2pp::Rect AdminExplosiones::corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                       const int32_t pos_x, const int32_t pos_y) {
    return {pos_x - coords_sprite.GetW() / 2, pos_y - coords_sprite.GetH() / 2,
            coords_sprite.GetW(), coords_sprite.GetH()};
}

AdminExplosiones::AdminExplosiones(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                                   Camara& camara):
        renderer(renderer),
        lector_texturas(lector_texturas),
        camara(camara),
        cantidad_frames_explosion(lector_texturas.obtener_coords_explosion().size()),
        siguiente_id_explosion(0) {}

void AdminExplosiones::agregar_explosion(const int pos_x, const int pos_y) {
    const std::vector<SDL2pp::Rect>& coords_sprite = lector_texturas.obtener_coords_explosion();
    const SDL2pp::Rect dimensiones_corregidas =
            corregir_desfase_sprite(coords_sprite.at(0), pos_x, pos_y);

    ObjetoAnimado nueva_explosion(siguiente_id_explosion, renderer,
                                  lector_texturas.obtener_textura_explosion(), coords_sprite,
                                  camara, dimensiones_corregidas, 0, ITERACIONES_POR_SPRITE, false);
    nueva_explosion.actualizar_animacion(
            {dimensiones_corregidas.GetX(), dimensiones_corregidas.GetY(), 1, 1}, 0, false);
    explosiones.emplace(siguiente_id_explosion, std::move(nueva_explosion));
    posicion_explosiones.emplace(
            siguiente_id_explosion,
            SDL2pp::Rect(dimensiones_corregidas.GetX(), dimensiones_corregidas.GetY(), 1, 1));
    siguiente_id_explosion++;
}

void AdminExplosiones::actualizar_animacion(const uint32_t iteraciones_actuales) {
    for (auto& [id, explosion]: explosiones) {
        explosion.actualizar_iteracion(iteraciones_actuales);
        const SDL2pp::Rect& sprite_actual = explosion.obtener_coords_sprite_actual();
        const SDL2pp::Rect dimensiones_corregidas =
                corregir_desfase_sprite(sprite_actual, posicion_explosiones.at(id).GetX(),
                                        posicion_explosiones.at(id).GetY());
        explosion.actualizar_animacion(
                {dimensiones_corregidas.GetX(), dimensiones_corregidas.GetY(), 1, 1}, 0, false);
    }
}

void AdminExplosiones::dibujar() {
    std::unordered_set<uint32_t> ids_eliminar;
    for (auto& [id, explosion]: explosiones) {
        explosion.dibujar();
        if (explosion.termino_animacion()) {
            ids_eliminar.insert(id);
        }
    }

    for (const auto& id: ids_eliminar) {
        explosiones.erase(id);
        posicion_explosiones.erase(id);
    }
}

AdminExplosiones::~AdminExplosiones() = default;
