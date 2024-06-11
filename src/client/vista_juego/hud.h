#ifndef HUD_H
#define HUD_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"

class HUD {
private:
    static const std::unordered_map<TipoArma, std::string> MAPA_TIPO_ARMA;
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture& textura_items;
    SDL2pp::Texture& textura_numeros;
    SDL2pp::Rect& coords_corazon;
    SDL2pp::Rect& coords_infinito;
    const std::unordered_map<TipoArma, SDL2pp::Rect>& coords_armas;
    const std::vector<SDL2pp::Rect>& coords_numeros;

    uint32_t puntos, vida;
    TipoArma arma_actual;
    int32_t balas_restantes;

    void dibujar_numero(uint32_t numero, int pos_x, int pos_y) const;

    void dibujar_puntos() const;
    void dibujar_vida() const;
    void dibujar_arma() const;

public:
    HUD(SDL2pp::Renderer& renderer, SDL2pp::Texture& textura_items,
        SDL2pp::Texture& textura_numeros, SDL2pp::Rect& coords_corazon,
        SDL2pp::Rect& coords_infinito,
        const std::unordered_map<TipoArma, SDL2pp::Rect>& coords_armas,
        const std::vector<SDL2pp::Rect>& coords_numeros);

    HUD(const HUD&) = delete;
    HUD& operator=(const HUD&) = delete;

    void actualizar(uint32_t puntos, uint32_t vida, TipoArma arma_actual, int32_t balas_restantes);

    void dibujar() const;

    ~HUD();
};


#endif  // HUD_H
