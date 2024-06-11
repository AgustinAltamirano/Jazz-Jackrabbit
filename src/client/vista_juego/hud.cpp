#include "hud.h"

#include "vista_juego_defs.h"

const std::unordered_map<TipoArma, std::string> HUD::MAPA_TIPO_ARMA{
        {INFINITA, "arma_infinita"},
        {ARMA1, "arma1"},
        {ARMA2, "arma2"},
        {ARMA3, "arma3"},
};

void HUD::dibujar_numero(uint32_t numero, int pos_x, const int pos_y) const {
    std::vector<uint8_t> cifras;
    while (numero > 0) {
        cifras.push_back(static_cast<uint8_t>(numero % 10));
        numero /= 10;
    }
    std::reverse(cifras.begin(), cifras.end());
    for (const auto cifra: cifras) {
        renderer.Copy(textura_numeros, coords_numeros.at(cifra),
                      SDL2pp::Rect(pos_x, pos_y, coords_numeros.at(cifra).GetW(),
                                   coords_numeros.at(cifra).GetH()));
        pos_x += coords_numeros.at(cifra).GetW() + SEPARACION_ENTRE_NUMEROS;
    }
}

void HUD::dibujar_puntos() const { dibujar_numero(puntos, POS_PUNTOS_X, POS_PUNTOS_Y); }

void HUD::dibujar_vida() const {
    int posicion_actual = POS_VIDA_X;
    renderer.Copy(textura_items, coords_corazon,
                  SDL2pp::Rect(posicion_actual, POS_VIDA_Y, coords_corazon.GetW(),
                               coords_corazon.GetH()));
    posicion_actual += coords_corazon.GetW() + SEPARACION_ENTRE_NUMEROS;
    dibujar_numero(vida, posicion_actual, POS_VIDA_Y);
}

void HUD::dibujar_arma() const {
    int posicion_actual = POS_ARMA_ACTUAL_X;
    renderer.Copy(
            textura_items, coords_armas.at(arma_actual),
            SDL2pp::Rect(posicion_actual, POS_ARMA_ACTUAL_Y, coords_armas.at(arma_actual).GetW(),
                         coords_armas.at(arma_actual).GetH()));
    posicion_actual += coords_armas.at(arma_actual).GetW() + SEPARACION_ENTRE_NUMEROS;
    if (balas_restantes < 0) {
        renderer.Copy(textura_items, coords_infinito,
                      SDL2pp::Rect(posicion_actual, POS_ARMA_ACTUAL_Y, coords_infinito.GetW(),
                                   coords_infinito.GetH()));
        return;
    }
    dibujar_numero(balas_restantes, posicion_actual, POS_ARMA_ACTUAL_Y);
}

HUD::HUD(SDL2pp::Renderer& renderer, SDL2pp::Texture& textura_items,
         SDL2pp::Texture& textura_numeros, SDL2pp::Rect& coords_corazon,
         SDL2pp::Rect& coords_infinito,
         const std::unordered_map<TipoArma, SDL2pp::Rect>& coords_armas,
         const std::vector<SDL2pp::Rect>& coords_numeros):
        renderer(renderer),
        textura_items(textura_items),
        textura_numeros(textura_numeros),
        coords_corazon(coords_corazon),
        coords_infinito(coords_infinito),
        coords_armas(coords_armas),
        coords_numeros(coords_numeros),
        puntos(0),
        vida(0),
        arma_actual(INFINITA),
        balas_restantes(-1) {}

void HUD::actualizar(const uint32_t puntos, const uint32_t vida, const TipoArma arma_actual,
                     const int32_t balas_restantes) {
    this->puntos = puntos;
    this->vida = vida;
    this->arma_actual = arma_actual;
    this->balas_restantes = balas_restantes;
}

void HUD::dibujar() const {
    dibujar_puntos();
    dibujar_vida();
    dibujar_arma();
}

HUD::~HUD() = default;
