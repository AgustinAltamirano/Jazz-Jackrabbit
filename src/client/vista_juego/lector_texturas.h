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
#define DIR_PERSONAJES "/personajes/"
#define PERSONAJES_CONFIG "/personajes.yaml"

#define COLOR_KEY_RED 44
#define COLOR_KEY_GREEN 102
#define COLOR_KEY_BLUE 150

#define COLOR_KEY_FORMATO \
    ((COLOR_KEY_RED << 24) + (COLOR_KEY_BLUE << 16) + (COLOR_KEY_GREEN << 8) + COLOR_KEY_RED)

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

    /**
     * Iterador externo genérico de @code LectorTexturas@endcode. Recorre simultáneamente un mapa de
     * texturas y su correspondiente mapa de coordenadas de animaciones. Estos mapas se pueden pasar
     * como parámetro al crear una instancia de @code IteradorTexturas@endcode, pero se recomienda
     * fuertemente no construirlos de forma directa. Esta clase fue diseñada para ser instanciada
     * mediante los métodos comenzados en @code begin@endcode y @code end@endcode de
     * @code LectorTexturas@endcode.
     *
     * El orden de iteración es el siguiente: Se comienza en la primera textura y en su primera
     * animación correspondiente. Al avanzar el iterador, se pasa a la siguiente animación de la
     * misma textura. Al llegar a la última animación de tal textura, se pasa a la siguiente textura
     * y a su primera animación. La iteración continúa de esta forma hasta haber recorrido todas las
     * texturas.
     */
    class IteradorTexturas {
    private:
        /** Referencia al mapa de texturas sobre el cual se desea iterar. */
        std::unordered_map<std::string, SDL2pp::Texture>& texturas;

        /** Referencia al mapa de animaciones sobre el cual se desea iterar. */
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<SDL2pp::Rect>>>&
                coords;

        /** Iterador del mapa de texturas. */
        std::unordered_map<std::string, SDL2pp::Texture>::iterator iterador_texturas;

        /** Iterador del mapa de animaciones. */
        std::unordered_map<std::string, std::vector<SDL2pp::Rect>>::const_iterator
                iterador_animaciones;

    public:
        IteradorTexturas(
                std::unordered_map<std::string, SDL2pp::Texture>& texturas,
                std::unordered_map<std::string,
                                   std::unordered_map<std::string, std::vector<SDL2pp::Rect>>>&
                        coords,
                std::unordered_map<std::string, SDL2pp::Texture>::iterator iterador_texturas,
                std::unordered_map<std::string, std::vector<SDL2pp::Rect>>::const_iterator
                        iterador_animaciones);

        /** Avanza a la siguiente iteración. */
        IteradorTexturas& operator++();

        bool operator==(const IteradorTexturas& otro) const;

        bool operator!=(const IteradorTexturas& otro) const;

        /** Obtiene el nombre del objeto (la clave) actual de la iteración. */
        [[nodiscard]] const std::string& obtener_nombre_objeto_actual() const;

        /** Obtiene la textura actual de la iteración. */
        [[nodiscard]] SDL2pp::Texture& obtener_textura_actual() const;

        /** Obtiene el nombre de la animación (la clave) actual de la iteración. */
        [[nodiscard]] const std::string& obtener_nombre_animacion_actual() const;

        /** Obtiene las coordenadas de la animación actual de la iteración. */
        [[nodiscard]] const std::vector<SDL2pp::Rect>& obtener_coordenadas_actuales() const;
    };

    /** Crea un @code IteradorTexturas@endcode al inicio de todas las texturas y animaciones de
     * personajes, según el orden de iteración descrito (véase la documentación de
     * @code IteradorTexturas@endcode).
     */
    IteradorTexturas beginPersonajes();

    /** Crea un @code IteradorTexturas@endcode al final de todas las texturas y animaciones de
     * personajes, según el orden de iteración descrito (véase la documentación de
     * @code IteradorTexturas@endcode).
     */
    IteradorTexturas endPersonajes();
};


#endif  // LECTOR_TEXTURAS_H
