#ifndef ADMIN_EXPLOSIONES_H
#define ADMIN_EXPLOSIONES_H

#include <cstdint>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "lector_texturas.h"
#include "objeto_animado.h"

class AdminExplosiones {
private:
    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::unordered_map<uint32_t, ObjetoAnimado> explosiones;
    std::unordered_map<uint32_t, SDL2pp::Rect> posicion_explosiones;
    const uint16_t cantidad_frames_explosion;
    uint32_t siguiente_id_explosion;

    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              int32_t pos_x, int32_t pos_y);

public:
    AdminExplosiones(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminExplosiones(const AdminExplosiones&) = delete;
    AdminExplosiones& operator=(const AdminExplosiones&) = delete;

    void agregar_explosion(int pos_x, int pos_y);

    void actualizar_animacion(uint32_t iteraciones_actuales);

    void dibujar();

    ~AdminExplosiones();
};


#endif  // ADMIN_EXPLOSIONES_H
