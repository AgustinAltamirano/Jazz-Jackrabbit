#ifndef ADMIN_BALAS_H
#define ADMIN_BALAS_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"

#include "camara.h"
#include "lector_texturas.h"
#include "objeto_animado.h"
#include "reproductor_sonido.h"


class AdminBalas {
private:
    static const std::unordered_map<TipoArma, const std::string> MAPA_TIPO_ARMA;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    ReproductorSonido reproductor_sonido_impacto_bala;
    std::vector<ObjetoAnimado> balas;
    uint32_t iteraciones_ultimo_sonido_impacto_bala;
    bool reproducir_sonido;

    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              int32_t pos_x, int32_t pos_y);

public:
    AdminBalas(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara,
               SDL2pp::Mixer& mixer);

    AdminBalas(const AdminBalas&) = delete;
    AdminBalas& operator=(const AdminBalas&) = delete;

    void eliminar_balas();

    void agregar_bala(TipoArma tipo_arma, int32_t pos_x, int32_t pos_y);

    void preparar_sonido_impacto_bala(uint32_t iteraciones_actuales);

    void dibujar_balas() const;

    void reproducir_sonido_pendiente();

    ~AdminBalas();
};

#endif  // ADMIN_BALAS_H
