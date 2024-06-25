#ifndef ADMINISTRADOR_VISTA_JUEGO_H
#define ADMINISTRADOR_VISTA_JUEGO_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "../../common/estado_personaje.h"
#include "../../common/queue.h"
#include "../../common/snapshot_dto.h"
#include "../../common/tipo_bloque_escenario.h"
#include "../../common/tipo_escenario.h"
#include "../../common/tipo_personaje.h"
#include "../juego/cliente.h"

#include "admin_balas.h"
#include "admin_enemigos.h"
#include "admin_explosiones.h"
#include "admin_recogibles.h"
#include "admin_sonidos.h"
#include "bloque_escenario.h"
#include "camara.h"
#include "entrada_juego.h"
#include "fondo_escenario.h"
#include "hud.h"
#include "lector_texturas.h"
#include "personaje.h"
#include "reproductor_musica.h"


/**
 * La clase @code AdministradorVistaJuego@endcode se encarga de crear y gestionar todos los objetos
 * visuales dentro del juego, asignándoles sus texturas y decidiendo cuándo se deben renderizar.
 * Además se encarga de sincronizar la vista, de forma de mantener una tasa de frames constante.
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

    /** Mixer de sonidos de SDL */
    SDL2pp::Mixer mixer;
    LectorTexturas lector_texturas;
    EntradaJuego entrada_juego;
    HUD hud;
    Cliente& cliente;

    /** Cantidad de iteraciones actuales del bucle principal de la vista. */
    uint32_t iteraciones_actuales;
    Camara camara;
    TipoEscenario tipo_escenario;
    std::optional<FondoEscenario> fondo_escenario;

    /** Mapa con todos los objetos asociados a personajes jugables. */
    std::unordered_map<uint32_t, Personaje> personajes;

    /** Mapa con todos los objetos asociados a bloques del escenario. */
    std::unordered_map<uint32_t, std::unique_ptr<BloqueEscenario>> bloques_escenario;

    /** Clase que administra la vista de todos los enemigos. */
    AdminEnemigos enemigos;

    /** Clase que administra la vista de todas las balas */
    AdminBalas balas;

    /** Clase que administra la vista de todos los objetos recogibles */
    AdminRecogibles recogibles;

    /** Clase que administra la vista de todas las explosiones */
    AdminExplosiones explosiones;

    ReproductorMusica reproductor_musica;
    AdminSonidos admin_sonidos;

    bool primera_snapshot_recibida;
    bool fin_juego;

    void actualizar_vista_fondo_escenario(TipoEscenario tipo_escenario);

    void actualizar_vista_camara_y_hud(const std::vector<ClienteDTO>& clientes_recibidos,
                                       int tiempo_restante);

    void actualizar_vista_bloques_escenario(
            const std::vector<BloqueEscenarioDTO>& bloques_recibidos);

    void actualizar_vista_personajes(const std::vector<ClienteDTO>& clientes_recibidos);

    void actualizar_vista_enemigos(const std::vector<EnemigoDTO>& enemigos_recibidos);

    void actualizar_vista_balas_y_explosiones(const std::vector<BalaDTO>& balas_recibidas);

    void actualizar_vista_recogibles(const std::vector<RecogibleDTO>& recogibles_recibidos);

    void actualizar_sonidos(const std::shared_ptr<SnapshotDTO>& snapshot);

    /** @brief Lee las snapshots de juego pendientes y actualiza la vista del juego en base a ellas.
     */
    void actualizar_vista();

    /**
     * @brief Sincroniza la vista del juego, de forma de mantener una tasa de frames constante.
     * @param ticks_transcurridos Milisegundos transcurridos desde la iteración anterior del bucle
     * principal
     * @returns Corrección de tiempo a aplicar en la próxima iteración del bucle principal
     */
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
