#ifndef ADMIN_SONIDOS_H
#define ADMIN_SONIDOS_H

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "reproductor_sonido.h"
#include "tipo_sonido.h"

class AdminSonidos {
private:
    SDL2pp::Mixer& mixer;
    std::unordered_map<TipoSonido, ReproductorSonido> reproductores_sonido;
    std::unordered_map<TipoSonido, uint32_t> iteraciones_ultimo_sonido;
    std::unordered_map<TipoSonido, bool> sonido_listo;

public:
    explicit AdminSonidos(SDL2pp::Mixer& mixer);

    AdminSonidos(const AdminSonidos&) = delete;
    AdminSonidos& operator=(const AdminSonidos&) = delete;

    void preparar_sonido(TipoSonido tipo_sonido, uint32_t iteraciones_actuales);

    void reproducir_sonidos();

    ~AdminSonidos();
};


#endif  // ADMIN_SONIDOS_H
