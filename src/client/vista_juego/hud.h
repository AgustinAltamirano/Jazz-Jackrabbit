#ifndef HUD_H
#define HUD_H

#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"
#include "../../common/tipo_personaje.h"

#include "lector_texturas.h"
#include "top_jugadores.h"
#include "vista_juego_defs.h"

/**
 * @class HUD
 * @brief Clase que representa el HUD (Head-Up Display) en el juego. Se encarga de mostrar
 * también la pantalla de carga y la pantalla de fin de juego.
 */
class HUD {
private:
    static const std::unordered_map<TipoArma, std::string> MAPA_TIPO_ARMA;
    static const std::unordered_map<TipoPersonaje, std::string> MAPA_TIPO_PERSONAJE;
    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    TopJugadores top_jugadores;

    // Datos a mostrar en el HUD
    const int32_t id_jugador;
    TipoPersonaje tipo_personaje;
    uint32_t puntos, vida;
    TipoArma arma_actual;
    int32_t balas_restantes;
    int tiempo_restante;

    /**
     * @brief Dibuja un número en la posición (pos_x, pos_y) de la pantalla.
     * @param numero Número a dibujar.
     * @param pos_x Posición x en la pantalla.
     * @param pos_y Posición y en la pantalla.
     * @param comenzar_desde_derecha Indica si se debe comenzar a dibujar el número desde la
     * derecha.
     */
    void dibujar_numero(uint32_t numero, int& pos_x, int pos_y,
                        bool comenzar_desde_derecha = false) const;

    /**
     * @brief Dibuja un texto en la posición (pos_x, pos_y) de la pantalla.
     * @param texto Texto a dibujar.
     * @param pos_x Posición x en la pantalla.
     * @param pos_y Posición y en la pantalla.
     */
    void dibujar_texto(const std::string& texto, int& pos_x, int pos_y) const;

    void dibujar_puntos() const;
    void dibujar_vida() const;
    void dibujar_arma() const;
    void dibujar_id_jugador() const;
    void dibujar_tiempo_restante() const;

public:
    HUD(int32_t id_jugador, SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas);

    HUD(const HUD&) = delete;
    HUD& operator=(const HUD&) = delete;

    /**
     * @brief Actualiza el HUD con los datos actuales del jugador
     * @param tipo_personaje Tipo de personaje
     * @param puntos Puntos del jugador
     * @param vida Vida del jugador
     * @param arma_actual Arma actual del jugador
     * @param balas_restantes Balas restantes del jugador
     * @param tiempo_restante Tiempo restante en el juego
     */
    void actualizar(TipoPersonaje tipo_personaje, uint32_t puntos, uint32_t vida,
                    TipoArma arma_actual, int32_t balas_restantes, int tiempo_restante);

    /**
     * @brief Actualiza el top de jugadores
     * @param jugadores Vector de tuplas con el id, puntos y tipo de personaje de los jugadores
     */
    void actualizar_top_jugadores(
            std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>>&& jugadores);

    /**
     * @brief Dibuja el HUD
     */
    void dibujar() const;

    /**
     * @brief Dibuja la pantalla de carga
     */
    void dibujar_pantalla_carga() const;

    /**
     * @brief Dibuja el top de jugadores
     * @param dibujar_todos Indica si se deben dibujar todos los jugadores o solo los primeros 3
     * @param pos_y Posición en el eje Y donde se debe comenzar a dibujar
     */
    void dibujar_top_jugadores(bool dibujar_todos, int pos_y = POS_TOP_JUGADORES_Y);

    /**
     * @brief Dibuja la pantalla de fin de juego
     */
    void dibujar_pantalla_fin_juego();

    ~HUD();
};


#endif  // HUD_H
