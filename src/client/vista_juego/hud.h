#ifndef HUD_H
#define HUD_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"
#include "../../common/tipo_personaje.h"

#include "lector_texturas.h"

class HUD {
private:
    static const std::unordered_map<TipoArma, std::string> MAPA_TIPO_ARMA;
    static const std::unordered_map<TipoPersonaje, std::string> MAPA_TIPO_PERSONAJE;
    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;

    const int32_t id_jugador;
    TipoPersonaje tipo_personaje;
    uint32_t puntos, vida;
    TipoArma arma_actual;
    int32_t balas_restantes;

    void dibujar_numero(uint32_t numero, int pos_x, int pos_y,
                        bool comenzar_desde_derecha = false) const;

    void dibujar_puntos() const;
    void dibujar_vida() const;
    void dibujar_arma() const;
    void dibujar_id_jugador() const;

public:
    HUD(int32_t id_jugador, SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas);

    HUD(const HUD&) = delete;
    HUD& operator=(const HUD&) = delete;

    void actualizar(TipoPersonaje tipo_personaje, uint32_t puntos, uint32_t vida,
                    TipoArma arma_actual, int32_t balas_restantes);

    void dibujar() const;

    ~HUD();
};


#endif  // HUD_H
