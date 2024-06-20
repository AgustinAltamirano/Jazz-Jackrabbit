#include "admin_sonidos.h"

#include "vista_juego_defs.h"

AdminSonidos::AdminSonidos(SDL2pp::Mixer& mixer): mixer(mixer) {
    reproductores_sonido.try_emplace(SONIDO_IMPACTO_BALA, mixer,
                                     ASSETS_PATH RUTA_SONIDOS ARCHIVO_SONIDO_IMPACTO_BALA);
    reproductores_sonido.try_emplace(SONIDO_DISPARO, mixer,
                                     ASSETS_PATH RUTA_SONIDOS ARCHIVO_SONIDO_DISPARO);
    reproductores_sonido.try_emplace(SONIDO_DANIO, mixer,
                                     ASSETS_PATH RUTA_SONIDOS ARCHIVO_SONIDO_DANIO);
    reproductores_sonido.try_emplace(SONIDO_MUERTE, mixer,
                                     ASSETS_PATH RUTA_SONIDOS ARCHIVO_SONIDO_MUERTE);
    reproductores_sonido.try_emplace(SONIDO_EXPLOSION, mixer,
                                     ASSETS_PATH RUTA_SONIDOS ARCHIVO_SONIDO_EXPLOSION);

    iteraciones_ultimo_sonido.emplace(SONIDO_IMPACTO_BALA, 0);
    iteraciones_ultimo_sonido.emplace(SONIDO_DISPARO, 0);
    iteraciones_ultimo_sonido.emplace(SONIDO_DANIO, 0);
    iteraciones_ultimo_sonido.emplace(SONIDO_MUERTE, 0);
    iteraciones_ultimo_sonido.emplace(SONIDO_EXPLOSION, 0);

    sonido_listo.emplace(SONIDO_IMPACTO_BALA, false);
    sonido_listo.emplace(SONIDO_DISPARO, false);
    sonido_listo.emplace(SONIDO_DANIO, false);
    sonido_listo.emplace(SONIDO_MUERTE, false);
    sonido_listo.emplace(SONIDO_EXPLOSION, false);
}

void AdminSonidos::preparar_sonido(const TipoSonido tipo_sonido,
                                   const uint32_t iteraciones_actuales) {
    if (iteraciones_actuales - iteraciones_ultimo_sonido.at(tipo_sonido) <
        ITERACIONES_ENTRE_SONIDOS) {
        return;
    }
    iteraciones_ultimo_sonido.at(tipo_sonido) = iteraciones_actuales;
    sonido_listo.at(tipo_sonido) = true;
}

void AdminSonidos::reproducir_sonidos() {
    for (const auto& [tipo_sonido, listo]: sonido_listo) {
        if (listo) {
            reproductores_sonido.at(tipo_sonido).reproducir_sonido();
            sonido_listo.at(tipo_sonido) = false;
        }
    }
}

AdminSonidos::~AdminSonidos() = default;
