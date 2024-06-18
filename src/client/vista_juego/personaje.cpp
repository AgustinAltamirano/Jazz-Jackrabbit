#include "personaje.h"

#include <utility>
#include <vector>

#include "../../common/constantes.h"

const std::unordered_map<EstadoVisualPersonaje, const std::string>
        Personaje::MAPA_ESTADOS_PERSONAJE{{ESTADO_STAND, "stand"},
                                          {ESTADO_CORRER, "correr"},
                                          {ESTADO_DASH, "dash"},
                                          {ESTADO_DISPARAR, "disparar"},
                                          {ESTADO_SALTAR_ARRIBA, "saltar_arriba"},
                                          {ESTADO_CAER_ABAJO, "caer_abajo"},
                                          {ESTADO_SALTAR_ADELANTE, "saltar_adelante"},
                                          {ESTADO_CAER_ADELANTE, "caer_adelante"},
                                          {ESTADO_ATAQUE_ESPECIAL, "ataque_especial"},
                                          {ESTADO_INTOXICADO_IDLE, "intoxicado_idle"},
                                          {ESTADO_INTOXICADO_CAMINAR, "intoxicado_caminar"},
                                          {ESTADO_DANIO, "danio"},
                                          {ESTADO_MUERTE, "muerte"}};

const std::unordered_map<EstadoVisualPersonaje, bool> Personaje::MAPA_REPETIR_ANIMACION{
        {ESTADO_STAND, true},
        {ESTADO_CORRER, true},
        {ESTADO_DASH, true},
        {ESTADO_DISPARAR, true},
        {ESTADO_SALTAR_ARRIBA, true},
        {ESTADO_CAER_ABAJO, true},
        {ESTADO_SALTAR_ADELANTE, false},
        {ESTADO_CAER_ADELANTE, true},
        {ESTADO_ATAQUE_ESPECIAL, false},
        {ESTADO_INTOXICADO_IDLE, true},
        {ESTADO_INTOXICADO_CAMINAR, true},
        {ESTADO_DANIO, false},
        {ESTADO_MUERTE, false}};

const std::unordered_map<EstadoVisualPersonaje, bool> Personaje::MAPA_CENTRAR_SPRITE{
        {ESTADO_STAND, false},
        {ESTADO_CORRER, false},
        {ESTADO_DASH, false},
        {ESTADO_DISPARAR, false},
        {ESTADO_SALTAR_ARRIBA, false},
        {ESTADO_CAER_ABAJO, false},
        {ESTADO_SALTAR_ADELANTE, false},
        {ESTADO_CAER_ADELANTE, false},
        {ESTADO_ATAQUE_ESPECIAL, false},
        {ESTADO_INTOXICADO_IDLE, false},
        {ESTADO_INTOXICADO_CAMINAR, false},
        {ESTADO_DANIO, true},
        {ESTADO_MUERTE, true}};

SDL2pp::Rect Personaje::corregir_desfase_sprite(const EstadoVisualPersonaje estado,
                                                const SDL2pp::Rect& dimensiones) const {
    const SDL2pp::Rect& coords_sprite =
            animaciones.at(estado_actual).obtener_coords_sprite_actual();

    if (MAPA_CENTRAR_SPRITE.at(estado)) {
        return {dimensiones.GetX() - (coords_sprite.GetW() - ANCHO_INICIAL) / 2,
                dimensiones.GetY() - (coords_sprite.GetH() - ALTO_INICIAL), dimensiones.GetW(),
                dimensiones.GetH()};
    }

    if (invertido) {
        return {dimensiones.GetX() - (coords_sprite.GetW() - ANCHO_INICIAL),
                dimensiones.GetY() - (coords_sprite.GetH() - ALTO_INICIAL), dimensiones.GetW(),
                dimensiones.GetH()};
    }
    return {dimensiones.GetX(), dimensiones.GetY() - (coords_sprite.GetH() - ALTO_INICIAL),
            dimensiones.GetW(), dimensiones.GetH()};
}

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
    for (const auto& [estado, nombre_estado]: MAPA_ESTADOS_PERSONAJE) {
        const std::vector<SDL2pp::Rect>& coords_animacion =
                lector_texturas.obtener_coords_personaje(this->nombre_personaje, nombre_estado);
        SDL2pp::Rect dimensiones_iniciales(pos_x, pos_y, coords_animacion.at(0).GetW() * 2,
                                           coords_animacion.at(0).GetH() * 2);
        ObjetoAnimado objeto_animacion(
                estado, renderer, lector_texturas.obtener_textura_personaje(this->nombre_personaje),
                coords_animacion, camara, dimensiones_iniciales, angulo, iteraciones_por_sprite,
                MAPA_REPETIR_ANIMACION.at(estado));
        animaciones.emplace(estado, std::move(objeto_animacion));
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
    animaciones.at(estado_actual).actualizar_iteracion(iteraciones_actuales);

    const SDL2pp::Rect dimensiones_corregidas = corregir_desfase_sprite(estado, dimensiones);

    animaciones.at(estado_actual).actualizar_animacion(dimensiones_corregidas, angulo, invertido);
}

void Personaje::actualizar_camara() const {
    animaciones.at(estado_actual)
            .actualizar_camara(pos_x + ANCHO_INICIAL / 2, pos_y + ALTO_INICIAL / 2);
}


void Personaje::dibujar() const { animaciones.at(estado_actual).dibujar(); }

Personaje::~Personaje() = default;
