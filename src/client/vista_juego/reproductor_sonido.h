#ifndef REPRODUCTOR_SONIDO_H
#define REPRODUCTOR_SONIDO_H

#include <string>

#include <SDL2pp/SDL2pp.hh>

/**
 * @class ReproductorSonido
 * @brief Representa un efecto de sonido del juego.
 */
class ReproductorSonido {
private:
    SDL2pp::Mixer& mixer;
    SDL2pp::Chunk sonido;

public:
    ReproductorSonido(SDL2pp::Mixer& mixer, const std::string& ruta_sonido);

    ReproductorSonido(const ReproductorSonido&) = delete;

    ReproductorSonido& operator=(const ReproductorSonido&) = delete;

    ReproductorSonido(ReproductorSonido&&) noexcept = default;

    /**
     * @brief Reproduce el efecto de sonido.
     */
    void reproducir_sonido() const;

    ~ReproductorSonido();
};


#endif  // REPRODUCTOR_SONIDO_H
