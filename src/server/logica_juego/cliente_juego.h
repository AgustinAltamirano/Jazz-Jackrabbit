#ifndef CLIENTE_JUEGO_H_
#define CLIENTE_JUEGO_H_

#include <cstdint>

#include "../../common/tipo_personaje.h"

class ClienteJuego {
private:
    const std::int32_t id;
    const TipoPersonaje personaje;

public:
    explicit ClienteJuego(const std::int32_t& id, const TipoPersonaje& personaje);

    std::int32_t obtener_id();

    TipoPersonaje obtener_personaje();

    ~ClienteJuego();
};

#endif  // CLIENTE_JUEGO_H_
