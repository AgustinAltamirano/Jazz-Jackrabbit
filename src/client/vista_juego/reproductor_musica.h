#ifndef REPRODUCTOR_MUSICA_H
#define REPRODUCTOR_MUSICA_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_escenario.h"

class ReproductorMusica {
private:
    static const std::unordered_map<TipoEscenario, std::string> MAPA_MUSICA;
    SDL2pp::Mixer& mixer;
    std::unique_ptr<SDL2pp::Music> musica_ambiente;
    SDL2pp::Music musica_fin_juego;
    bool reproduciendo;

public:
    explicit ReproductorMusica(SDL2pp::Mixer& mixer);

    ReproductorMusica(const ReproductorMusica&) = delete;

    ReproductorMusica& operator=(const ReproductorMusica&) = delete;

    void reproducir_musica_ambiente(TipoEscenario tipo_escenario);

    void detener_musica_ambiente();

    [[nodiscard]] bool esta_reproduciendo_musica_ambiente() const;

    void reproducir_musica_fin_juego() const;

    ~ReproductorMusica();
};


#endif  // REPRODUCTOR_MUSICA_H
