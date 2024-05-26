#ifndef PERSONAJEJAZZ_H
#define PERSONAJEJAZZ_H

#include <string>
#include <vector>

#include "personaje.h"

#define NOMBRE_PERSONAJE_JAZZ "jazz"

/** Clase que representa a un personaje visual con la apariencia de Jazz. */
class PersonajeJazz final: public Personaje {
public:
    PersonajeJazz(uint32_t id, SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                  const std::vector<int>& dimensiones_iniciales, unsigned int frames_por_sprite,
                  unsigned int frame_ticks_actuales);

    PersonajeJazz(const PersonajeJazz&) = delete;

    PersonajeJazz& operator=(const PersonajeJazz&) = delete;

    ~PersonajeJazz() override;
};

#endif  // PERSONAJEJAZZ_H
