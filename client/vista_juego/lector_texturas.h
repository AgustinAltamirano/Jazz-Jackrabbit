#ifndef LECTOR_TEXTURAS_H
#define LECTOR_TEXTURAS_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

/**
 * Rutas usadas para cargar los sprites y las coordenadas de cada uno en sus respectivas imágenes.
 */
#define RUTA_SPRITES "/sprites"
#define DIR_PERSONAJES "/personajes"
#define PERSONAJES_CONFIG "/personajes.yaml"

/**
 * La clase LectorTexturas se encarga de cargar las texturas y las coordenadas de los sprites.
 * En cada una de las subcarpetas de @code RUTA_SPRITES@endcode se encuentran las imágenes de las
 * texturas, además de los archivos YAML que determinan las coordenadas de cada uno de los sprites
 * de cada animación.
 */
class LectorTexturas {
private:
    /** Renderer utilizado por el juego para mostrar la interfaz gráfica. */
    SDL2pp::Renderer& renderer;

    /** Mapa que contiene las texturas de todos los personajes jugables. */
    std::unordered_map<std::string, SDL2pp::Texture> texturas_personajes;

    /** Mapa que contiene las coordenadas de todos los sprites de personajes jugables. */
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<SDL2pp::Rect>>>
            coords_personajes;

public:
    explicit LectorTexturas(SDL2pp::Renderer& renderer);

    LectorTexturas(LectorTexturas&) = delete;
    LectorTexturas& operator=(LectorTexturas&) = delete;

    /** Carga todas las texturas y coordenadas disponibles en @code RUTA_SPRITES@endcode. */
    void cargar_texturas_y_coordenadas();

    /**
     * Obtiene la textura correspondiente al nombre de un personaje jugable.
     * @param personaje nombre del personaje
     * @return referencia a la textura del personaje
     */
    const SDL2pp::Texture& obtener_textura_personaje(const std::string& personaje);

    /**
     * Obtiene las coordenadas de todos los sprites de una animación de un personaje jugable.
     * @param personaje nombre del personaje
     * @param animacion nombre de la animación del personaje
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_personaje(const std::string& personaje,
                                                              const std::string& animacion) const;

    ~LectorTexturas();
};

#endif  // LECTOR_TEXTURAS_H
