#include "bloque_escenario.h"

BloqueEscenario::BloqueEscenario(const int render_x, const int render_y, const int render_ancho,
                                 const int render_alto, SDL2pp::Renderer& renderer,
                                 SDL2pp::Texture& textura_superficie,
                                 SDL2pp::Texture& textura_relleno,
                                 const SDL2pp::Rect& coords_superficie,
                                 const SDL2pp::Rect& coords_relleno):
        render_x(render_x),
        render_y(render_y),
        render_ancho(render_ancho),
        render_alto(render_alto),
        renderer(renderer),
        textura_superficie(textura_superficie),
        textura_relleno(textura_relleno),
        coords_superficie(coords_superficie),
        coords_relleno(coords_relleno) {}

BloqueEscenario::~BloqueEscenario() = default;
