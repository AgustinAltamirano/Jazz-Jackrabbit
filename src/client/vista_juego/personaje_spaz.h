#ifndef PERSONAJE_SPAZ_H
#define PERSONAJE_SPAZ_H

#include <string>
#include <vector>

#include "personaje.h"

#define NOMBRE_PERSONAJE_SPAZ "spaz"

/** Clase que representa a un personaje visual con la apariencia de Spaz. */
class PersonajeSpaz final: public Personaje {
public:
    PersonajeSpaz(uint32_t id, SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas,
                  const std::vector<int>& dimensiones_iniciales, unsigned int frames_por_sprite,
                  unsigned int frame_ticks_actuales);

    PersonajeSpaz(const PersonajeSpaz&) = delete;

    PersonajeSpaz& operator=(const PersonajeSpaz&) = delete;

    ~PersonajeSpaz() override;
};

#endif  // PERSONAJE_SPAZ_H
