#include "admin_enemigos.h"

#include <string>
#include <unordered_set>
#include <utility>

#include "vista_juego_defs.h"

const std::unordered_map<TipoEnemigo, const std::string> AdminEnemigos::MAPA_TIPO_ENEMIGO{
        {LAGARTO, "lagarto"},
        {ESQUELETO, "esqueleto"},
        {MURCIELAGO, "murcielago"},
};

SDL2pp::Rect AdminEnemigos::corregir_desfase_sprite(const uint32_t id_enemigo,
                                                    const SDL2pp::Rect& dimensiones,
                                                    const bool invertido) const {
    const SDL2pp::Rect& coords_sprite = enemigos.at(id_enemigo).obtener_coords_sprite_actual();
    if (invertido) {
        return {dimensiones.GetX() - (coords_sprite.GetW() - dimensiones.GetW()),
                dimensiones.GetY() - (coords_sprite.GetH() - dimensiones.GetH()),
                dimensiones.GetW(), dimensiones.GetH()};
    }
    return {dimensiones.GetX(), dimensiones.GetY() - (coords_sprite.GetH() - dimensiones.GetH()),
            dimensiones.GetW(), dimensiones.GetH()};
}

AdminEnemigos::AdminEnemigos(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                             Camara& camara):
        renderer(renderer), lector_texturas(lector_texturas), camara(camara) {}

bool AdminEnemigos::existe_enemigo(const uint32_t id_enemigo) const {
    return enemigos.count(id_enemigo) > 0;
}

void AdminEnemigos::agregar_enemigo(const int32_t id_enemigo, const TipoEnemigo tipo,
                                    const SDL2pp::Rect dimensiones_iniciales, bool invertido) {
    if (existe_enemigo(id_enemigo)) {
        return;
    }

    ObjetoAnimado nuevo_enemigo(id_enemigo, renderer, lector_texturas.obtener_textura_enemigos(),
                                lector_texturas.obtener_coords_enemigo(MAPA_TIPO_ENEMIGO.at(tipo)),
                                camara,
                                {dimensiones_iniciales.GetX(), dimensiones_iniciales.GetY(),
                                 FACTOR_ESCALA_SPRITES, FACTOR_ESCALA_SPRITES},
                                0, ITERACIONES_POR_SPRITE);
    enemigos.emplace(id_enemigo, std::move(nuevo_enemigo));
    contador_enemigos[id_enemigo] = ITERACIONES_HASTA_ELIMINAR;
}

void AdminEnemigos::actualizar_animacion(const uint32_t id_enemigo,
                                         const uint32_t iteraciones_actuales,
                                         const SDL2pp::Rect& dimensiones, const bool invertido) {
    if (!existe_enemigo(id_enemigo)) {
        return;
    }

    enemigos.at(id_enemigo).actualizar_iteracion(iteraciones_actuales);

    const SDL2pp::Rect dimensiones_corregidas =
            corregir_desfase_sprite(id_enemigo, dimensiones, invertido);

    enemigos.at(id_enemigo)
            .actualizar_animacion({dimensiones_corregidas.GetX(), dimensiones_corregidas.GetY(),
                                   FACTOR_ESCALA_SPRITES, FACTOR_ESCALA_SPRITES},
                                  0, invertido);
    contador_enemigos[id_enemigo] = ITERACIONES_HASTA_ELIMINAR;
}

void AdminEnemigos::dibujar_enemigos() {
    std::unordered_set<uint32_t> ids_enemigos_a_eliminar;
    for (auto& [id, contador]: contador_enemigos) {
        if (contador <= 0) {
            enemigos.erase(id);
            ids_enemigos_a_eliminar.insert(id);
        }
    }

    for (auto& id: ids_enemigos_a_eliminar) {
        contador_enemigos.erase(id);
    }

    for (const auto& [id, enemigo]: enemigos) {
        enemigo.dibujar();
        contador_enemigos.at(id)--;
    }
}

AdminEnemigos::~AdminEnemigos() = default;
