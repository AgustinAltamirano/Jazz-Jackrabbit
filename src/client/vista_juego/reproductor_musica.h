#ifndef REPRODUCTOR_MUSICA_H
#define REPRODUCTOR_MUSICA_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_escenario.h"

/**
 * @class ReproductorMusica
 * @brief Clase responsable de la gestión y reproducción de la música del juego.
 */
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

    /**
     * @brief Reproduce la música para un escenario de juego específico.
     * @param tipo_escenario El tipo del escenario de juego.
     */
    void reproducir_musica_ambiente(TipoEscenario tipo_escenario);

    /**
     * @brief Detiene la reproducción de la música del ambiente del juego.
     */
    void detener_musica_ambiente();

    /**
     * @brief Verifica si la música del ambiente del juego se está reproduciendo actualmente.
     * @return true si la música está reproduciéndose, false en caso contrario.
     */
    [[nodiscard]] bool esta_reproduciendo_musica_ambiente() const;

    /**
     * @brief Reproduce la música para el final del juego.
     */
    void reproducir_musica_fin_juego() const;

    ~ReproductorMusica();
};


#endif  // REPRODUCTOR_MUSICA_H
