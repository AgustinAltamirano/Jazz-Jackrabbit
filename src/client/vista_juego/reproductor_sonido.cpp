#include "reproductor_sonido.h"

ReproductorSonido::ReproductorSonido(SDL2pp::Mixer& mixer, const std::string& ruta_sonido):
        mixer(mixer), sonido(ruta_sonido) {}

void ReproductorSonido::reproducir_sonido() const { mixer.PlayChannel(-1, sonido, 0); }

ReproductorSonido::~ReproductorSonido() = default;
