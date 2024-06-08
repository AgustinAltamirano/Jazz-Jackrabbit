#include "objeto_animado.h"

#include <SDL2/SDL_render.h>

ObjetoAnimado::ObjetoAnimado(const uint32_t id, SDL2pp::Renderer& renderer,
                             SDL2pp::Texture& textura,
                             const std::vector<SDL2pp::Rect>& sprite_coords, Camara& camara,
                             const SDL2pp::Rect& dimensiones_iniciales, const int angulo,
                             const uint32_t iteraciones_por_sprite):
        id(id),
        renderer(renderer),
        textura(textura),
        camara(camara),
        sprite_coords(sprite_coords),
        render_coords(camara.obtener_coords_ventana(dimensiones_iniciales)),
        render_angulo(angulo),
        invertido(false),
        reseteado(true),
        sprite_actual(0),
        iteraciones_por_sprite(iteraciones_por_sprite) {}

ObjetoAnimado::ObjetoAnimado(ObjetoAnimado&& otro) noexcept:
        id(otro.id),
        renderer(otro.renderer),
        textura(otro.textura),
        camara(otro.camara),
        sprite_coords(otro.sprite_coords),
        render_coords(otro.render_coords),
        render_angulo(otro.render_angulo),
        invertido(otro.invertido),
        reseteado(otro.reseteado),
        sprite_actual(otro.sprite_actual),
        iteraciones_por_sprite(otro.iteraciones_por_sprite) {
    // La otra instancia de ObjetoAnimado se deja con valores válidos
    otro.render_coords = SDL2pp::Rect(0, 0, 0, 0);
    otro.render_angulo = 0;
    otro.invertido = false;
    otro.reseteado = true;
    otro.sprite_actual = 0;
}

void ObjetoAnimado::resetear_animacion() { reseteado = true; }

void ObjetoAnimado::actualizar_animacion(const uint32_t iteraciones_actuales,
                                         const SDL2pp::Rect& dimensiones, const int angulo,
                                         const bool invertido) {
    sprite_actual =
            !reseteado ? (iteraciones_actuales / iteraciones_por_sprite) % sprite_coords.size() : 0;
    reseteado = false;

    this->invertido = invertido;

    const SDL2pp::Rect nuevas_coords_absolutas(
            dimensiones.GetX(), dimensiones.GetY(),
            sprite_coords.at(sprite_actual).GetW() * dimensiones.GetW(),
            sprite_coords.at(sprite_actual).GetH() * dimensiones.GetH());
    render_coords = camara.obtener_coords_ventana(nuevas_coords_absolutas);
    render_angulo = angulo;
}

void ObjetoAnimado::actualizar_camara(const int camara_pos_x, const int camara_pos_y) const {
    const SDL2pp::Rect& coords_actual = sprite_coords.at(0);
    camara.actualizar_pos_camara(camara_pos_x + coords_actual.GetW() / 2,
                                 camara_pos_y + coords_actual.GetH() / 2);
}


void ObjetoAnimado::dibujar() const {
    if (!Camara::esta_dentro_de_ventana(render_coords)) {
        return;
    }
    const int flip_flag = invertido ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    renderer.Copy(textura, sprite_coords.at(sprite_actual),
                  SDL2pp::Optional<SDL2pp::Rect>(render_coords), render_angulo, SDL2pp::NullOpt,
                  flip_flag);
}

ObjetoAnimado::~ObjetoAnimado() = default;
