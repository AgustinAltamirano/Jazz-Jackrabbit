#ifndef CLIENTE_JUEGO_H_
#define CLIENTE_JUEGO_H_

#include <cstdint>

class ClienteJuego {
public:
    ClienteJuego(std::int32_t id);

    std::int32_t obtener_id();

    ~ClienteJuego();

private:
    const std::int32_t id;

};

#endif  // CLIENTE_JUEGO_H_
