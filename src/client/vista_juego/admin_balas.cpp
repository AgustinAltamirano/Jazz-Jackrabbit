#include "admin_balas.h"

#include <string>
#include <utility>
#include <vector>

const std::unordered_map<TipoArma, const std::string> AdminBalas::MAPA_TIPO_ARMA{
        {INFINITA, "infinita"},
        {ARMA1, "arma1"},
        {ARMA2, "arma2"},
        {ARMA3, "arma3"},
};

SDL2pp::Rect AdminBalas::corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                 const int32_t pos_x, const int32_t pos_y) {
    return {pos_x - coords_sprite.GetW() / 2, pos_y - coords_sprite.GetH() / 2,
            coords_sprite.GetW(), coords_sprite.GetH()};
}

AdminBalas::AdminBalas(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara):
        renderer(renderer), lector_texturas(lector_texturas), camara(camara) {}

void AdminBalas::eliminar_balas() { balas.clear(); }

void AdminBalas::agregar_bala(const TipoArma tipo_arma, const int32_t pos_x, const int32_t pos_y) {
    const std::vector<SDL2pp::Rect>& coords_sprite =
            lector_texturas.obtener_coords_bala(MAPA_TIPO_ARMA.at(tipo_arma));
    const SDL2pp::Rect dimensiones_corregidas =
            corregir_desfase_sprite(coords_sprite.at(0), pos_x, pos_y);

    ObjetoAnimado nueva_bala(0, renderer, lector_texturas.obtener_textura_items(), coords_sprite,
                             camara, dimensiones_corregidas, 0, ITERACIONES_POR_SPRITE);
    nueva_bala.actualizar_animacion(
            {dimensiones_corregidas.GetX(), dimensiones_corregidas.GetY(), 1, 1}, 0, false);
    balas.push_back(std::move(nueva_bala));
}

void AdminBalas::dibujar_balas() const {
    for (const auto& bala: balas) {
        bala.dibujar();
    }
}

AdminBalas::~AdminBalas() = default;
