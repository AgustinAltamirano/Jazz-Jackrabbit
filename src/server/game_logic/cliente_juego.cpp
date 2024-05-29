#include "cliente_juego.h"


ClienteJuego::ClienteJuego(std::int32_t id) : id(id) {}

std::int32_t ClienteJuego::obtener_id() {
    return id;
}