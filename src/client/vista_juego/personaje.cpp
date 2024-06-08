#include "personaje.h"

#include <utility>

const std::unordered_map<EstadoVisualPersonaje, const std::string>
        Personaje::mapa_estados_personaje{{ESTADO_STAND, "stand"},
                                          {ESTADO_CORRER, "correr"},
                                          {ESTADO_DASH, "dash"},
                                          {ESTADO_DISPARAR, "disparar"},
                                          {ESTADO_SALTAR_ARRIBA, "saltar_arriba"},
                                          {ESTADO_CAER_ABAJO, "caer_abajo"},
                                          {ESTADO_SALTAR_ADELANTE, "saltar_adelante"},
                                          {ESTADO_CAER_ADELANTE, "caer_adelante"},
                                          {ESTADO_ATAQUE_ESPECIAL, "ataque_especial"}};

Personaje::Personaje(const uint32_t id, std::string nombre_personaje, SDL2pp::Renderer& renderer,
                     LectorTexturas& lector_texturas, Camara& camara, const int pos_x,
                     const int pos_y, const int angulo, const uint32_t iteraciones_por_sprite):
        id(id),
        nombre_personaje(std::move(nombre_personaje)),
        estado_actual(ESTADO_STAND),
        pos_x(pos_x),
        pos_y(pos_y),
        angulo(angulo),
        invertido(false),
        iteraciones_por_sprite(iteraciones_por_sprite) {
    for (const auto& [first, second]: mapa_estados_personaje) {
        const std::vector<SDL2pp::Rect>& coords_animacion =
                lector_texturas.obtener_coords_personaje(this->nombre_personaje, second);
        SDL2pp::Rect dimensiones_iniciales(pos_x, pos_y, coords_animacion.at(0).GetW() * 2,
                                           coords_animacion.at(0).GetH() * 2);
        ObjetoAnimado objeto_animacion(
                first, renderer, lector_texturas.obtener_textura_personaje(this->nombre_personaje),
                coords_animacion, camara, dimensiones_iniciales, angulo, iteraciones_por_sprite);
        animaciones.emplace(first, std::move(objeto_animacion));
    }
}
Personaje::Personaje(Personaje&& otro) noexcept:
        id(otro.id),
        nombre_personaje(otro.nombre_personaje),
        estado_actual(otro.estado_actual),
        pos_x(otro.pos_x),
        pos_y(otro.pos_y),
        angulo(otro.angulo),
        invertido(otro.invertido),
        iteraciones_por_sprite(otro.iteraciones_por_sprite),
        animaciones(std::move(otro.animaciones)) {
    otro.estado_actual = ESTADO_INDEFINIDO;
    otro.pos_x = 0;
    otro.pos_y = 0;
    otro.angulo = 0;
    otro.invertido = false;
}

void Personaje::actualizar_animacion(const EstadoVisualPersonaje estado,
                                     const uint32_t iteraciones_actuales,
                                     const SDL2pp::Rect& dimensiones, const int angulo,
                                     const bool invertido) {
    this->invertido = invertido;
    pos_x = dimensiones.GetX();
    pos_y = dimensiones.GetY();
    this->angulo = angulo;
    if (estado != estado_actual) {
        animaciones.at(estado_actual).resetear_animacion();
        estado_actual = estado;
    }
    animaciones.at(estado_actual)
            .actualizar_animacion(iteraciones_actuales, dimensiones, angulo, invertido);
}

void Personaje::actualizar_camara() const {
    animaciones.at(estado_actual).actualizar_camara(pos_x, pos_y);
}


void Personaje::dibujar() const { animaciones.at(estado_actual).dibujar(); }

Personaje::~Personaje() = default;
