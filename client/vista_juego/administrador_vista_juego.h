#ifndef ADMINISTRADOR_VISTA_JUEGO_H
#define ADMINISTRADOR_VISTA_JUEGO_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "../../common/queue.h"

#include "entrada_juego.h"
#include "lector_texturas.h"
#include "objeto_animado.h"
#include "personaje.h"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

/** Constantes definidas únicamente para realizar tests preliminares. */
#define X_INICIAL 100
#define Y_INICIAL 50
#define X_INICIAL2 300
#define Y_INICIAL2 50
#define X_INICIAL3 100
#define Y_INICIAL3 250
#define X_INICIAL4 300
#define Y_INICIAL4 250
#define FRAMES_POR_SPRITE 100

/**
 * La clase @code AdministradorVistaJuego@endcode se encarga de asignar las texturas y animaciones
 * cargadas por una instancia de @code LectorTexturas@endcode a todos los objetos visuales dentro
 * del juego, además de decidir cuáles de ellos se deben renderizar en cada momento y cuáles no.
 */
class AdministradorVistaJuego {
private:
    uint32_t proximo_id;

    /** Inicializador de la librería SDL. */
    SDL2pp::SDL sdl;

    SDL2pp::Window ventana;
    SDL2pp::Renderer renderer;
    LectorTexturas lector_texturas;
    EntradaJuego entrada_juego;

    /** Mapa con todos los objetos asociados a personajes jugables. */
    std::unordered_map<uint32_t, Personaje> personajes;

public:
    AdministradorVistaJuego(const std::string& titulo_ventana, Queue<int>& cola_acciones);

    AdministradorVistaJuego(AdministradorVistaJuego&) = delete;
    AdministradorVistaJuego& operator=(AdministradorVistaJuego&) = delete;

    /** Bucle principal del administrador de vista de juego. */
    void run();

    ~AdministradorVistaJuego();
};

#endif  // ADMINISTRADOR_VISTA_JUEGO_H
