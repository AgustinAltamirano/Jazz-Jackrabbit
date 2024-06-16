#ifndef ADMIN_BALAS_H
#define ADMIN_BALAS_H

#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"

#include "camara.h"
#include "lector_texturas.h"
#include "objeto_animado.h"


class AdminBalas {
private:
    static const std::unordered_map<TipoArma, const std::string> MAPA_TIPO_ARMA;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::vector<ObjetoAnimado> balas;

    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              int32_t pos_x, int32_t pos_y);

public:
    AdminBalas(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminBalas(const AdminBalas&) = delete;
    AdminBalas& operator=(const AdminBalas&) = delete;

    void eliminar_balas();

    void agregar_bala(TipoArma tipo_arma, int32_t pos_x, int32_t pos_y);

    void dibujar_balas() const;

    ~AdminBalas();
};


#endif  // ADMIN_BALAS_H
