#ifndef PERSONAJE_LORI_H
#define PERSONAJE_LORI_H

#include <string>
#include <vector>

#include "personaje.h"

#define NOMBRE_PERSONAJE_LORI "lori"

/** Clase que representa a un personaje visual con la apariencia de Lori. */
class PersonajeLori final: public Personaje {
public:
    PersonajeLori(uint32_t id, SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                  const std::vector<int>& dimensiones_iniciales, unsigned int frames_por_sprite,
                  unsigned int frame_ticks_actuales);

    PersonajeLori(const PersonajeLori&) = delete;

    PersonajeLori& operator=(const PersonajeLori&) = delete;

    ~PersonajeLori() override;
};

#endif  // PERSONAJE_LORI_H
