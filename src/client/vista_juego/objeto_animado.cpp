#include "objeto_animado.h"

#include <SDL2/SDL_render.h>

ObjetoAnimado::ObjetoAnimado(const uint32_t id, SDL2pp::Renderer& renderer,
                             SDL2pp::Texture& textura,
                             const std::vector<SDL2pp::Rect>& sprite_coords, Camara& camara,
                             const SDL2pp::Rect& dimensiones_iniciales, const int angulo,
                             const uint32_t iteraciones_por_sprite, const bool repetir):
        id(id),
        renderer(renderer),
        textura(textura),
        camara(camara),
        sprite_coords(sprite_coords),
        render_coords(camara.obtener_coords_ventana(dimensiones_iniciales)),
        render_angulo(angulo),
        invertido(false),
        reseteado(true),
        repetir(repetir),
        sprite_actual(0),
        iteraciones_inicio_animacion(0),
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
        repetir(otro.repetir),
        sprite_actual(otro.sprite_actual),
        iteraciones_inicio_animacion(otro.iteraciones_inicio_animacion),
        iteraciones_por_sprite(otro.iteraciones_por_sprite) {
    // La otra instancia de ObjetoAnimado se deja con valores válidos
    otro.render_coords = SDL2pp::Rect(0, 0, 0, 0);
    otro.render_angulo = 0;
    otro.invertido = false;
    otro.reseteado = true;
    otro.sprite_actual = 0;
    otro.iteraciones_inicio_animacion = 0;
}

const SDL2pp::Rect& ObjetoAnimado::obtener_coords_sprite_actual() const {
    return sprite_coords.at(sprite_actual);
}

void ObjetoAnimado::resetear_animacion() {
    reseteado = true;
    sprite_actual = 0;
}

void ObjetoAnimado::actualizar_iteracion(const uint32_t iteraciones_actuales) {
    if (reseteado) {
        iteraciones_inicio_animacion = iteraciones_actuales;
    }

    if (repetir) {
        sprite_actual = (iteraciones_actuales / iteraciones_por_sprite) % sprite_coords.size();
        reseteado = false;
        return;
    }

    if (const uint16_t sprite_actual_aux =
                (iteraciones_actuales - iteraciones_inicio_animacion) / iteraciones_por_sprite;
        sprite_actual_aux >= sprite_coords.size()) {
        sprite_actual = sprite_coords.size() - 1;
    } else {
        sprite_actual = sprite_actual_aux;
    }
    reseteado = false;
}

void ObjetoAnimado::actualizar_animacion(const SDL2pp::Rect& dimensiones, const int angulo,
                                         const bool invertido) {
    this->invertido = invertido;
    const SDL2pp::Rect nuevas_coords_absolutas(
            dimensiones.GetX(), dimensiones.GetY(),
            sprite_coords.at(sprite_actual).GetW() * dimensiones.GetW(),
            sprite_coords.at(sprite_actual).GetH() * dimensiones.GetH());
    render_coords = camara.obtener_coords_ventana(nuevas_coords_absolutas);
    render_angulo = angulo;
}

void ObjetoAnimado::actualizar_camara(const int camara_pos_x, const int camara_pos_y) const {
    camara.actualizar_pos_camara(camara_pos_x, camara_pos_y);
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
