#ifndef ADMIN_SONIDOS_H
#define ADMIN_SONIDOS_H

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "reproductor_sonido.h"
#include "tipo_sonido.h"

/**
 * @class AdminSonidos
 * @brief Clase encargada de administrar la reproducción de efectos de sonido en el juego.
 */
class AdminSonidos {
private:
    SDL2pp::Mixer& mixer;
    std::unordered_map<TipoSonido, ReproductorSonido> reproductores_sonido;

    /** Mapa que contiene el número de iteración donde se produjo el último sonido de cada tipo. */
    std::unordered_map<TipoSonido, uint32_t> iteraciones_ultimo_sonido;

    /** Mapa que indica por cada tipo de sonido si se ha seleccionado para reproducirse */
    std::unordered_map<TipoSonido, bool> sonido_listo;

public:
    explicit AdminSonidos(SDL2pp::Mixer& mixer);

    AdminSonidos(const AdminSonidos&) = delete;
    AdminSonidos& operator=(const AdminSonidos&) = delete;

    /**
     * @brief Prepara un sonido para ser reproducido
     * @param tipo_sonido Tipo de sonido
     * @param iteraciones_actuales Número de iteraciones actuales
     */
    void preparar_sonido(TipoSonido tipo_sonido, uint32_t iteraciones_actuales);

    /**
     * @brief Reproduce los sonidos que están listos
     */
    void reproducir_sonidos();

    ~AdminSonidos();
};


#endif  // ADMIN_SONIDOS_H
