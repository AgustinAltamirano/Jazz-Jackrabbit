#include "personaje.h"

#include <utility>

std::unordered_map<EstadoPersonaje, const std::string> Personaje::mapa_estados_personaje{
        {STAND, "stand"},
        {CORRER, "correr"},
        {CARGAR_DASH, "cargar_dash"},
        {DASH, "dash"},
        {PARAR_DASH, "parar_dash"},
        {DISPARAR, "disparar"},
        {PARAR_DISPARAR, "parar_disparar"},
        {CARGAR_SALTAR_ARRIBA, "cargar_saltar_arriba"},
        {SALTAR_ARRIBA, "saltar_arriba"},
        {SALTAR_COSTADO, "saltar_costado"},
        {CAER, "caer"}};

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
