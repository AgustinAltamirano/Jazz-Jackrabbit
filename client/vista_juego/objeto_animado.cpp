#include "objeto_animado.h"

ObjetoAnimado::ObjetoAnimado(const uint32_t id, SDL2pp::Renderer& renderer,
                             SDL2pp::Texture& textura,
                             const std::vector<SDL2pp::Rect>& sprite_coords,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        id(id),
        renderer(renderer),
        textura(textura),
        sprite_coords(sprite_coords),
        render_x(dimensiones_iniciales.at(RENDER_X)),
        render_y(dimensiones_iniciales.at(RENDER_Y)),
        render_ancho(dimensiones_iniciales.at(RENDER_ANCHO)),
        render_alto(dimensiones_iniciales.at(RENDER_ALTO)),
        render_angulo(dimensiones_iniciales.at(RENDER_ANGULO)),
        invertido(false),
        sprite_actual(0),
        frames_por_sprite(frames_por_sprite),
        frame_ticks_anteriores(frame_ticks_actuales) {}

ObjetoAnimado::ObjetoAnimado(ObjetoAnimado&& otro) noexcept:
        id(otro.id),
        renderer(otro.renderer),
        textura(otro.textura),
        sprite_coords(otro.sprite_coords),
        render_x(otro.render_x),
        render_y(otro.render_y),
        render_ancho(otro.render_ancho),
        render_alto(otro.render_alto),
        render_angulo(otro.render_angulo),
        invertido(otro.invertido),
        sprite_actual(otro.sprite_actual),
        frames_por_sprite(otro.frames_por_sprite),
        frame_ticks_anteriores(otro.frame_ticks_anteriores) {
    // La otra instancia de ObjetoAnimado se deja con valores válidos
    otro.render_x = 0;
    otro.render_y = 0;
    otro.render_ancho = 0;
    otro.render_alto = 0;
    otro.render_angulo = 0;
    otro.invertido = false;
    otro.sprite_actual = 0;
}

void ObjetoAnimado::resetear_animacion() { sprite_actual = 0; }

void ObjetoAnimado::actualizar_animacion(const unsigned int frame_ticks_transcurridos,
                                         const std::vector<int>& dimensiones) {
    invertido = dimensiones.at(RENDER_X) - render_x < 0;
    render_x = dimensiones.at(RENDER_X);
    render_y = dimensiones.at(RENDER_Y);

    if (const int nuevo_ancho = dimensiones.at(RENDER_ANCHO) >= 0) {
        render_ancho = nuevo_ancho;
    }

    if (const int nuevo_alto = dimensiones.at(RENDER_ANCHO) >= 0) {
        render_ancho = nuevo_alto;
    }

    render_angulo = dimensiones.at(RENDER_ANGULO);
    sprite_actual = ((frame_ticks_transcurridos - frame_ticks_anteriores) / frames_por_sprite) %
                    sprite_coords.size();
    frame_ticks_anteriores = frame_ticks_transcurridos;
}

void ObjetoAnimado::dibujar() const {
    const int flip_flag = invertido ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    renderer.Copy(textura, sprite_coords.at(sprite_actual),
                  SDL2pp::Optional<SDL2pp::Rect>(
                          SDL2pp::Rect(render_x, render_y, render_ancho, render_alto)),
                  (double)render_angulo, SDL2pp::NullOpt, flip_flag);
}

ObjetoAnimado::~ObjetoAnimado() = default;
