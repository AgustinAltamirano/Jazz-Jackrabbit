#include "personaje.h"

#include <utility>

std::unordered_map<EstadoPersonaje, const std::string> Personaje::mapa_estados_personaje{
        {STAND, "stand"},
        {CORRER, "correr"},
        {DASH, "dash"},
        {DISPARAR, "disparar"},
        {PARAR_DISPARAR, "parar_disparar"},
        {CARGAR_SALTAR_ARRIBA, "cargar_saltar_arriba"},
        {SALTAR_ARRIBA, "saltar_arriba"},
        {PARAR_SALTAR_ARRIBA, "parar_saltar_arriba"},
        {CAER_ABAJO, "caer_abajo"},
        {SALTAR_ADELANTE, "saltar_adelante"},
        {CAER_ADELANTE, "caer_adelante"}};

Personaje::Personaje(const uint32_t id, std::string nombre_personaje, SDL2pp::Renderer& renderer,
                     LectorTexturas& lector_texturas, const std::vector<int>& dimensiones_iniciales,
                     const unsigned int frames_por_sprite, const unsigned int frame_ticks_actuales):
        id(id),
        nombre_personaje(std::move(nombre_personaje)),
        estado_actual(STAND),
        render_x(dimensiones_iniciales.at(RENDER_X)),
        render_y(dimensiones_iniciales.at(RENDER_Y)),
        render_angulo(dimensiones_iniciales.at(RENDER_ANGULO)),
        invertido(false),
        frames_por_sprite(frames_por_sprite),
        frame_ticks_anteriores(frame_ticks_actuales) {
    for (const auto& [first, second]: mapa_estados_personaje) {
        ObjetoAnimado objeto_animacion(
                first, renderer, lector_texturas.obtener_textura_personaje(this->nombre_personaje),
                lector_texturas.obtener_coords_personaje(this->nombre_personaje, second),
                dimensiones_iniciales, frames_por_sprite, frame_ticks_actuales);
        animaciones.emplace(first, std::move(objeto_animacion));
    }
}
Personaje::Personaje(Personaje&& otro) noexcept:
        id(otro.id),
        nombre_personaje(otro.nombre_personaje),
        estado_actual(otro.estado_actual),
        render_x(otro.render_x),
        render_y(otro.render_y),
        render_angulo(otro.render_angulo),
        invertido(otro.invertido),
        frames_por_sprite(otro.frames_por_sprite),
        frame_ticks_anteriores(otro.frame_ticks_anteriores),
        animaciones(std::move(otro.animaciones)) {
    otro.estado_actual = INDEFINIDO;
    otro.render_x = 0;
    otro.render_y = 0;
    otro.render_angulo = 0;
    otro.invertido = false;
    otro.frame_ticks_anteriores = 0;
}

void Personaje::actualizar_animacion(const EstadoPersonaje estado,
                                     const unsigned int frame_ticks_transcurridos,
                                     const std::vector<int>& dimensiones) {
    if (dimensiones.at(RENDER_X) - render_x < 0) {
        invertido = true;
    } else if (dimensiones.at(RENDER_X) - render_x > 0) {
        invertido = false;
    }
    render_x = dimensiones.at(RENDER_X);
    render_y = dimensiones.at(RENDER_Y);
    render_angulo = dimensiones.at(RENDER_ANGULO);
    frame_ticks_anteriores += frame_ticks_transcurridos;
    if (estado != estado_actual) {
        animaciones.at(estado_actual).resetear_animacion();
        estado_actual = estado;
    }
    animaciones.at(estado_actual)
            .actualizar_animacion(frame_ticks_transcurridos, dimensiones, invertido);
}

void Personaje::dibujar() const { animaciones.at(estado_actual).dibujar(); }

Personaje::~Personaje() = default;
