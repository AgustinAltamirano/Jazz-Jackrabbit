#ifndef ADMINISTRADOR_VISTA_JUEGO_H
#define ADMINISTRADOR_VISTA_JUEGO_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>

#include "../../common/comando_dto.h"
#include "../../common/estado_personaje.h"
#include "../../common/queue.h"
#include "../../common/snapshot_dto.h"
#include "../../common/tipo_bloque_escenario.h"
#include "../../common/tipo_escenario.h"
#include "../../common/tipo_personaje.h"
#include "../juego/cliente.h"

#include "bloque_escenario.h"
#include "camara.h"
#include "entrada_juego.h"
#include "fondo_escenario.h"
#include "hud.h"
#include "lector_texturas.h"
#include "objeto_animado.h"
#include "pantalla_carga.h"
#include "personaje.h"
#include "vista_juego_defs.h"

/**
 * La clase @code AdministradorVistaJuego@endcode se encarga de asignar las texturas y animaciones
 * cargadas por una instancia de @code LectorTexturas@endcode a todos los objetos visuales dentro
 * del juego, además de decidir cuáles de ellos se deben renderizar en cada momento y cuáles no.
 */
class AdministradorVistaJuego {
private:
    static const std::unordered_map<TipoEscenario, std::string> MAPA_TIPO_ESCENARIO;
    static const std::unordered_map<TipoBloqueEscenario, std::string> MAPA_TIPO_BLOQUE;
    static const std::unordered_map<TipoPersonaje, std::string> MAPA_TIPO_PERSONAJE;
    static const std::unordered_map<EstadoPersonaje, EstadoVisualPersonaje> MAPA_ESTADOS_PERSONAJE;

    uint32_t id_jugador;
    uint32_t proximo_id;

    /** Inicializador de la librería SDL. */
    SDL2pp::SDL sdl;

    SDL2pp::Window ventana;
    SDL2pp::Renderer renderer;
    PantallaCarga pantalla_carga;
    LectorTexturas lector_texturas;
    EntradaJuego entrada_juego;
    HUD hud;
    Cliente& cliente;

    uint32_t iteraciones_actuales;
    Camara camara;
    TipoEscenario tipo_escenario;
    std::optional<FondoEscenario> fondo_escenario;
    /** Mapa con todos los objetos asociados a personajes jugables. */
    std::unordered_map<uint32_t, Personaje> personajes;

    /** Mapa con todos los objetos asociados a bloques del escenario. */
    std::unordered_map<uint32_t, std::unique_ptr<BloqueEscenario>> bloques_escenario;

    /** Mapa con todos los objetos asociados a enemigos. */
    std::unordered_map<uint32_t, ObjetoAnimado> enemigos;

    bool primera_snapshot_recibida;
    bool fin_juego;

    void actualizar_vista_fondo_escenario(TipoEscenario tipo_escenario);

    void actualizar_vista_camara_y_hud(const std::vector<ClienteDTO>& clientes_recibidos);

    void actualizar_vista_bloques_escenario(const std::vector<BloqueEscenarioDTO>& bloques_recibidos);

    void actualizar_vista_personajes(const std::vector<ClienteDTO>& clientes_recibidos);

    void actualizar_vista();

    int64_t sincronizar_vista(int64_t ticks_transcurridos);

public:
    AdministradorVistaJuego(int32_t id_cliente, const std::string& titulo_ventana,
                            Cliente& cliente);

    AdministradorVistaJuego(AdministradorVistaJuego&) = delete;
    AdministradorVistaJuego& operator=(AdministradorVistaJuego&) = delete;

    /** Bucle principal del administrador de vista de juego. */
    void run();

    ~AdministradorVistaJuego();
};

#endif  // ADMINISTRADOR_VISTA_JUEGO_H
