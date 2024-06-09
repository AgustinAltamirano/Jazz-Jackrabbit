#include "cliente_juego.h"


ClienteJuego::ClienteJuego(const std::int32_t& id, const TipoPersonaje& personaje):
        id(id), personaje(personaje) {}

std::int32_t ClienteJuego::obtener_id() { return id; }

TipoPersonaje ClienteJuego::obtener_personaje() { return personaje; }
