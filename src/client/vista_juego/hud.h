#ifndef HUD_H
#define HUD_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"

#include "lector_texturas.h"

class HUD {
private:
    static const std::unordered_map<TipoArma, std::string> MAPA_TIPO_ARMA;
    SDL2pp::Renderer& renderer;
    const LectorTexturas& lector_texturas;

    uint32_t puntos, vida;
    TipoArma arma_actual;
    int32_t balas_restantes;

    void dibujar_numero(uint32_t numero, int pos_x, int pos_y) const;

    void dibujar_puntos() const;
    void dibujar_vida() const;
    void dibujar_arma() const;

public:
    HUD(SDL2pp::Renderer& renderer, const LectorTexturas& lector_texturas);

    HUD(const HUD&) = delete;
    HUD& operator=(const HUD&) = delete;

    void actualizar(uint32_t puntos, uint32_t vida, TipoArma arma_actual, int32_t balas_restantes);

    void dibujar() const;

    ~HUD();
};


#endif  // HUD_H
