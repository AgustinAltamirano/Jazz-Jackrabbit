#include "objeto_animado.h"

#include <SDL2/SDL_render.h>

ObjetoAnimado::ObjetoAnimado(const uint32_t id, SDL2pp::Renderer& renderer,
                             SDL2pp::Texture& textura,
                             const std::vector<SDL2pp::Rect>& sprite_coords, const Camara& camara,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        id(id),
        renderer(renderer),
        textura(textura),
        sprite_coords(sprite_coords),
        camara(camara),
        render_coords(camara.obtener_coords_ventana(SDL2pp::Rect(
                dimensiones_iniciales.at(RENDER_X), dimensiones_iniciales.at(RENDER_Y),
                dimensiones_iniciales.at(RENDER_ANCHO), dimensiones_iniciales.at(RENDER_ALTO)))),
        render_angulo(dimensiones_iniciales.at(RENDER_ANGULO)),
        invertido(false),
        reseteado(true),
        sprite_actual(0),
        frames_por_sprite(frames_por_sprite),
        frame_ticks_anteriores(frame_ticks_actuales) {}

ObjetoAnimado::ObjetoAnimado(ObjetoAnimado&& otro) noexcept:
        id(otro.id),
        renderer(otro.renderer),
        textura(otro.textura),
        sprite_coords(otro.sprite_coords),
        camara(otro.camara),
        render_coords(otro.render_coords),
        render_angulo(otro.render_angulo),
        invertido(otro.invertido),
        reseteado(otro.reseteado),
        sprite_actual(otro.sprite_actual),
        frames_por_sprite(otro.frames_por_sprite),
        frame_ticks_anteriores(otro.frame_ticks_anteriores) {
    // La otra instancia de ObjetoAnimado se deja con valores válidos
    otro.render_coords = SDL2pp::Rect(0, 0, 0, 0);
    otro.render_angulo = 0;
    otro.invertido = false;
    otro.reseteado = true;
    otro.sprite_actual = 0;
}

void ObjetoAnimado::resetear_animacion() { reseteado = true; }

void ObjetoAnimado::actualizar_animacion(const unsigned int frame_ticks_transcurridos,
                                         const std::vector<int>& dimensiones,
                                         const bool invertido) {
    sprite_actual =
            !reseteado ?
                    ((frame_ticks_transcurridos + frame_ticks_anteriores) / frames_por_sprite) %
                            sprite_coords.size() :
                    0;
    reseteado = false;
    frame_ticks_anteriores += frame_ticks_transcurridos;

    this->invertido = invertido;

    const SDL2pp::Rect nuevas_coords_absolutas(
            dimensiones.at(RENDER_X), dimensiones.at(RENDER_Y),
            sprite_coords.at(sprite_actual).GetW() * dimensiones.at(RENDER_ANCHO),
            sprite_coords.at(sprite_actual).GetH() * dimensiones.at(RENDER_ALTO));
    render_coords = camara.obtener_coords_ventana(nuevas_coords_absolutas);
    render_angulo = dimensiones.at(RENDER_ANGULO);
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
