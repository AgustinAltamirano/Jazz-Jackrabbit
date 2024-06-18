#ifndef ADMIN_RECOGIBLES_H
#define ADMIN_RECOGIBLES_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_recogible.h"

#include "camara.h"
#include "lector_texturas.h"
#include "objeto_animado.h"


class AdminRecogibles {
private:
    static const std::unordered_map<TipoRecogible, const std::string> MAPA_TIPO_RECOGIBLE;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::vector<ObjetoAnimado> recogibles;

    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              const SDL2pp::Rect& dimensiones);

public:
    AdminRecogibles(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminRecogibles(const AdminRecogibles&) = delete;
    AdminRecogibles& operator=(const AdminRecogibles&) = delete;

    void eliminar_recogibles();

    void agregar_recogible(TipoRecogible tipo_recogible, const SDL2pp::Rect& dimensiones);

    void dibujar_recogibles() const;

    ~AdminRecogibles();
};

#endif  // ADMIN_RECOGIBLES_H
