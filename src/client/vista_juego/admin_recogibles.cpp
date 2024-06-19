#include "admin_recogibles.h"

#include <string>
#include <utility>
#include <vector>

const std::unordered_map<TipoRecogible, const std::string> AdminRecogibles::MAPA_TIPO_RECOGIBLE{
        {MONEDA_AGARRABLE, "moneda"},        {GEMA_AGARRABLE, "gema"},
        {MUNICION_ARMA_1, "municion_arma1"}, {MUNICION_ARMA_2, "municion_arma2"},
        {MUNICION_ARMA_3, "municion_arma3"}, {FRUTA_PODRIDA, "bebida_podrida"},
        {FRUTA_BUENA, "zanahoria"},
};

SDL2pp::Rect AdminRecogibles::corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                      const SDL2pp::Rect& dimensiones) {
    return {dimensiones.GetX(), dimensiones.GetY() - (coords_sprite.GetH() - dimensiones.GetH()),
            dimensiones.GetW(), dimensiones.GetH()};
}

AdminRecogibles::AdminRecogibles(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                                 Camara& camara):
        renderer(renderer), lector_texturas(lector_texturas), camara(camara) {}

void AdminRecogibles::eliminar_recogibles() { recogibles.clear(); }

void AdminRecogibles::agregar_recogible(const TipoRecogible tipo_recogible,
                                        const SDL2pp::Rect& dimensiones) {
    const std::vector<SDL2pp::Rect>& coords_sprite =
            lector_texturas.obtener_coords_recogible(MAPA_TIPO_RECOGIBLE.at(tipo_recogible));
    const SDL2pp::Rect dimensiones_corregidas =
            corregir_desfase_sprite(coords_sprite.at(0), dimensiones);

    ObjetoAnimado nuevo_recogible(0, renderer, lector_texturas.obtener_textura_items(),
                                  coords_sprite, camara, dimensiones_corregidas, 0,
                                  ITERACIONES_POR_SPRITE);
    nuevo_recogible.actualizar_animacion(
            {dimensiones_corregidas.GetX(), dimensiones_corregidas.GetY(), 1, 1}, 0, false);
    recogibles.push_back(std::move(nuevo_recogible));
}

void AdminRecogibles::dibujar_recogibles() const {
    for (const auto& recogible: recogibles) {
        recogible.dibujar();
    }
}

AdminRecogibles::~AdminRecogibles() = default;
