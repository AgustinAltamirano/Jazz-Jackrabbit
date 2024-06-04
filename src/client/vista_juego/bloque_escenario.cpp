#include "bloque_escenario.h"

BloqueEscenario::BloqueEscenario(const SDL2pp::Rect coords, SDL2pp::Renderer& renderer,
                                 SDL2pp::Texture& textura_superficie,
                                 SDL2pp::Texture& textura_relleno,
                                 const SDL2pp::Rect& coords_superficie,
                                 const SDL2pp::Rect& coords_relleno, const Camara& camara):
        coords(coords),
        render_coords(camara.obtener_coords_ventana(coords)),
        renderer(renderer),
        textura_superficie(textura_superficie),
        textura_relleno(textura_relleno),
        coords_superficie(coords_superficie),
        coords_relleno(coords_relleno),
        camara(camara) {}

void BloqueEscenario::actualizar_vista() { render_coords = camara.obtener_coords_ventana(coords); }

BloqueEscenario::~BloqueEscenario() = default;
