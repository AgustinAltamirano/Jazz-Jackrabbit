#ifndef ADMINISTRADOR_VISTA_JUEGO_H
#define ADMINISTRADOR_VISTA_JUEGO_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "../../common/accion_juego_dto.h"
#include "../../common/queue.h"

#include "entrada_juego.h"
#include "fondo_escenario.h"
#include "lector_texturas.h"
#include "objeto_animado.h"
#include "personaje.h"
#include "snapshot_dto.h"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

/**
 * La clase @code AdministradorVistaJuego@endcode se encarga de asignar las texturas y animaciones
 * cargadas por una instancia de @code LectorTexturas@endcode a todos los objetos visuales dentro
 * del juego, además de decidir cuáles de ellos se deben renderizar en cada momento y cuáles no.
 */
class AdministradorVistaJuego {
private:
    static const std::unordered_map<TipoEscenario, std::string> MAPA_TIPO_ESCENARIO;

    uint32_t proximo_id;

    /** Inicializador de la librería SDL. */
    SDL2pp::SDL sdl;

    SDL2pp::Window ventana;
    SDL2pp::Renderer renderer;
    LectorTexturas lector_texturas;
    EntradaJuego entrada_juego;
    Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots;

    TipoEscenario tipo_escenario;
    std::optional<FondoEscenario> fondo_escenario;
    /** Mapa con todos los objetos asociados a personajes jugables. */
    std::unordered_map<uint32_t, Personaje> personajes;

    void actualizar_vista();

public:
    AdministradorVistaJuego(const std::string& titulo_ventana,
                            Queue<std::shared_ptr<AccionJuegoDTO>>& cola_acciones,
                            Queue<std::shared_ptr<SnapshotDTO_provisorio>>& cola_snapshots);

    AdministradorVistaJuego(AdministradorVistaJuego&) = delete;
    AdministradorVistaJuego& operator=(AdministradorVistaJuego&) = delete;

    /** Bucle principal del administrador de vista de juego. */
    void run();

    ~AdministradorVistaJuego();
};

#endif  // ADMINISTRADOR_VISTA_JUEGO_H
