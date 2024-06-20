#ifndef LECTOR_TEXTURAS_H
#define LECTOR_TEXTURAS_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "vista_juego_defs.h"

/**
 * La clase LectorTexturas se encarga de cargar las texturas y las coordenadas de los sprites.
 */
class LectorTexturas {
private:
    SDL2pp::Renderer& renderer;

    std::unique_ptr<SDL2pp::Texture> textura_pantalla_carga;

    std::unordered_map<std::string, SDL2pp::Texture> texturas_escenarios;

    std::unordered_map<std::string, SDL2pp::Rect> coords_fondos_escenarios;

    std::unordered_map<std::string, std::unordered_map<std::string, SDL2pp::Rect>>
            coords_bloques_escenarios;

    std::unordered_map<std::string, SDL2pp::Texture> texturas_personajes;

    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<SDL2pp::Rect>>>
            coords_personajes;

    std::unique_ptr<SDL2pp::Texture> textura_enemigos;

    std::unordered_map<std::string, std::vector<SDL2pp::Rect>> coords_enemigos;

    std::unique_ptr<SDL2pp::Texture> textura_fuente;

    std::vector<SDL2pp::Rect> coords_numeros;

    std::unordered_map<std::string, SDL2pp::Rect> coords_simbolos;

    std::unordered_map<char, SDL2pp::Rect> coords_letras;

    std::unique_ptr<SDL2pp::Texture> textura_items;

    std::unordered_map<std::string, SDL2pp::Rect> coords_iconos;

    std::unordered_map<std::string, SDL2pp::Rect> coords_armas;

    std::unordered_map<std::string, std::vector<SDL2pp::Rect>> coords_balas;

    std::unordered_map<std::string, std::vector<SDL2pp::Rect>> coords_recogibles;

public:
    explicit LectorTexturas(SDL2pp::Renderer& renderer);

    LectorTexturas(LectorTexturas&) = delete;
    LectorTexturas& operator=(LectorTexturas&) = delete;

    /** Carga todas las texturas y coordenadas disponibles en @code RUTA_SPRITES@endcode. */
    void cargar_texturas_y_coordenadas();

    SDL2pp::Texture& obtener_textura_pantalla_carga() const;

    /**
     * Obtiene la textura correspondiente al nombre de un personaje jugable.
     * @param personaje nombre del personaje
     * @return referencia a la textura del personaje
     */
    SDL2pp::Texture& obtener_textura_personaje(const std::string& personaje);

    /**
     * Obtiene las coordenadas de todos los sprites de una animación de un personaje jugable.
     * @param personaje nombre del personaje
     * @param animacion nombre de la animación del personaje
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_personaje(const std::string& personaje,
                                                              const std::string& animacion) const;

    SDL2pp::Texture& obtener_textura_fondo_escenario(const std::string& tipo_escenario);

    const SDL2pp::Rect& obtener_coords_fondo_escenario(const std::string& tipo_escenario) const;

    SDL2pp::Texture& obtener_textura_bloque(const std::string& tipo_escenario);

    const SDL2pp::Rect& obtener_coords_bloque(const std::string& tipo_escenario,
                                              const std::string& tipo_bloque) const;

    SDL2pp::Texture& obtener_textura_enemigos() const;

    /**
     * Obtiene las coordenadas de todos los sprites de un enemigo
     * @param enemigo nombre del enemigo
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_enemigo(const std::string& enemigo) const;

    SDL2pp::Texture& obtener_textura_fuente() const;

    const std::vector<SDL2pp::Rect>& obtener_coords_numeros() const;

    const SDL2pp::Rect& obtener_coords_simbolo(const std::string& nombre_simbolo) const;

    const SDL2pp::Rect& obtener_coords_letra(char letra) const;

    SDL2pp::Texture& obtener_textura_items() const;

    const SDL2pp::Rect& obtener_coords_icono(const std::string& nombre_icono) const;

    const std::unordered_map<std::string, SDL2pp::Rect>& obtener_coords_armas() const;

    const std::vector<SDL2pp::Rect>& obtener_coords_bala(const std::string& nombre_arma) const;

    const std::vector<SDL2pp::Rect>& obtener_coords_recogible(
            const std::string& nombre_recogible) const;

    ~LectorTexturas();
};

#endif  // LECTOR_TEXTURAS_H
