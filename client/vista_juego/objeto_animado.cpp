#include "objeto_animado.h"

ObjetoAnimado::ObjetoAnimado(const uint32_t id, SDL2pp::Renderer& renderer,
                             SDL2pp::Texture& sprites,
                             const std::vector<SDL2pp::Rect>& sprite_states,
                             const std::vector<int>& dimensiones_iniciales,
                             const unsigned int frames_por_sprite,
                             const unsigned int frame_ticks_actuales):
        id(id),
        renderer(renderer),
        sprites(sprites),
        sprite_states(sprite_states),
        render_x(dimensiones_iniciales.at(RENDER_X)),
        render_y(dimensiones_iniciales.at(RENDER_Y)),
        render_ancho(dimensiones_iniciales.at(RENDER_ANCHO)),
        render_alto(dimensiones_iniciales.at(RENDER_ALTO)),
        render_angulo(dimensiones_iniciales.at(RENDER_ANGULO)),
        invertido(false),
        sprite_actual(0),
        frames_por_sprite(frames_por_sprite),
        frame_ticks_anteriores(frame_ticks_actuales) {}

void ObjetoAnimado::resetear_animacion() { sprite_actual = 0; }

void ObjetoAnimado::actualizar_animacion(const unsigned int frame_ticks_actuales,
                                         const std::vector<int>& dimensiones) {
    invertido = dimensiones.at(RENDER_X) - render_x < 0;
    render_x = dimensiones.at(RENDER_X);
    render_y = dimensiones.at(RENDER_Y);
    render_ancho = dimensiones.at(RENDER_ANCHO);
    render_alto = dimensiones.at(RENDER_ALTO);
    render_angulo = dimensiones.at(RENDER_ANGULO);
    sprite_actual = ((frame_ticks_actuales - frame_ticks_anteriores) / frames_por_sprite) %
                    sprite_states.size();
    frame_ticks_anteriores = frame_ticks_actuales;
}

void ObjetoAnimado::dibujar() const {
    const int flip_flag = invertido ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    renderer.Copy(sprites, sprite_states.at(sprite_actual),
                  SDL2pp::Optional<SDL2pp::Rect>(
                          SDL2pp::Rect(render_x, render_y, render_ancho, render_alto)),
                  (double)render_angulo, SDL2pp::NullOpt, flip_flag);
}

ObjetoAnimado::~ObjetoAnimado() = default;
