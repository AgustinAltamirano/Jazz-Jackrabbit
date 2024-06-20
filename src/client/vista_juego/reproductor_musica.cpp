#include "reproductor_musica.h"

#include "vista_juego_defs.h"

const std::unordered_map<TipoEscenario, std::string> ReproductorMusica::MAPA_MUSICA = {
        {ESCENARIO_CARROTUS, ASSETS_PATH RUTA_MUSICA MUSICA_CARROTUS},
        {ESCENARIO_CASTLE, ASSETS_PATH RUTA_MUSICA MUSICA_CASTLE}};


ReproductorMusica::ReproductorMusica(SDL2pp::Mixer& mixer):
        mixer(mixer),
        musica_fin_juego(ASSETS_PATH RUTA_MUSICA MUSICA_FIN_JUEGO),
        reproduciendo(false) {}

void ReproductorMusica::reproducir_musica_ambiente(const TipoEscenario tipo_escenario) {
    if (reproduciendo || !MAPA_MUSICA.count(tipo_escenario)) {
        return;
    }
    musica_ambiente = std::make_unique<SDL2pp::Music>(MAPA_MUSICA.at(tipo_escenario));
    mixer.SetMusicVolume(VOLUMEN_MUSICA);
    mixer.PlayMusic(*musica_ambiente);
    reproduciendo = true;
}

void ReproductorMusica::detener_musica_ambiente() {
    if (!reproduciendo) {
        return;
    }
    mixer.HaltMusic();
    reproduciendo = false;
}

bool ReproductorMusica::esta_reproduciendo_musica_ambiente() const { return reproduciendo; }

void ReproductorMusica::reproducir_musica_fin_juego() const {
    mixer.SetMusicVolume(VOLUMEN_MUSICA_FIN_JUEGO);
    mixer.PlayMusic(musica_fin_juego, 1);
}

ReproductorMusica::~ReproductorMusica() = default;
