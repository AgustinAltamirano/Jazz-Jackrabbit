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

#define DIR_ESCENARIOS "/escenarios/"
#define ESCENARIOS_CONFIG "/escenarios.yaml"

#define COLOR_KEY_PERSONAJES_RED 44
#define COLOR_KEY_PERSONAJES_GREEN 102
#define COLOR_KEY_PERSONAJES_BLUE 150

#define COLOR_KEY_PERSONAJES                                                \
    ((COLOR_KEY_PERSONAJES_RED << 24) + (COLOR_KEY_PERSONAJES_BLUE << 16) + \
     (COLOR_KEY_PERSONAJES_GREEN << 8) + COLOR_KEY_PERSONAJES_RED)

#define COLOR_KEY_ESCENARIOS_RED 87
#define COLOR_KEY_ESCENARIOS_GREEN 0
#define COLOR_KEY_ESCENARIOS_BLUE 203

#define COLOR_KEY_ESCENARIOS                                                \
    ((COLOR_KEY_ESCENARIOS_RED << 24) + (COLOR_KEY_ESCENARIOS_BLUE << 16) + \
     (COLOR_KEY_ESCENARIOS_GREEN << 8) + COLOR_KEY_ESCENARIOS_RED)

/**
 * La clase LectorTexturas se encarga de cargar las texturas y las coordenadas de los sprites.
 */
class LectorTexturas {
private:
    SDL2pp::Renderer& renderer;

    std::unordered_map<std::string, SDL2pp::Texture> texturas_escenarios;

    std::unordered_map<std::string, SDL2pp::Rect> coords_fondos_escenarios;

    std::unordered_map<std::string, std::unordered_map<std::string, SDL2pp::Rect>>
            coords_bloques_escenarios;

    std::unordered_map<std::string, SDL2pp::Texture> texturas_personajes;

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

    ~LectorTexturas();

    /**
     * Iterador externo genérico de @code LectorTexturas@endcode. Recorre simultáneamente un mapa de
     * texturas y su correspondiente mapa de coordenadas de animaciones. Se recomienda instanciar
     * esta clase únicamente mediante los métodos comenzados en @code begin@endcode y
     * @code end@endcode de @code LectorTexturas@endcode.
     */
    class IteradorTexturas {
    private:
        /** Referencia al mapa de texturas sobre el cual se desea iterar. */
        std::unordered_map<std::string, SDL2pp::Texture>& texturas;

        /** Referencia al mapa de animaciones sobre el cual se desea iterar. */
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<SDL2pp::Rect>>>&
                coords;

        std::unordered_map<std::string, SDL2pp::Texture>::iterator iterador_texturas;

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

        [[nodiscard]] const std::string& obtener_nombre_objeto_actual() const;

        [[nodiscard]] SDL2pp::Texture& obtener_textura_actual() const;

        [[nodiscard]] const std::string& obtener_nombre_animacion_actual() const;

        [[nodiscard]] const std::vector<SDL2pp::Rect>& obtener_coordenadas_actuales() const;
    };

    /**
     * Iterador externo genérico de todas las animaciones de una textura determinada de
     * @code LectorTexturas@endcode.
     */
    class IteradorAnimaciones {
    private:
        /** Referencia al mapa de animaciones sobre el cual se desea iterar. */
        std::unordered_map<std::string, std::vector<SDL2pp::Rect>>& coords;

        std::unordered_map<std::string, std::vector<SDL2pp::Rect>>::const_iterator
                iterador_animaciones;

    public:
        IteradorAnimaciones(
                std::unordered_map<std::string, std::vector<SDL2pp::Rect>>& animaciones,
                std::unordered_map<std::string, std::vector<SDL2pp::Rect>>::const_iterator
                        iterador_animaciones);

        /** Avanza a la siguiente iteración. */
        IteradorAnimaciones& operator++();

        bool operator==(const IteradorAnimaciones& otro) const;

        bool operator!=(const IteradorAnimaciones& otro) const;

        [[nodiscard]] const std::string& obtener_nombre_animacion_actual() const;

        [[nodiscard]] const std::vector<SDL2pp::Rect>& obtener_coordenadas_actuales() const;
    };

    /**
     * Crea un @code IteradorTexturas@endcode al inicio de todas las texturas y animaciones de
     * personajes.
     */
    IteradorTexturas begin_personajes();

    /**
     * Crea un @code IteradorTexturas@endcode al final de todas las texturas y animaciones de
     * personajes.
     */
    IteradorTexturas end_personajes();

    /**
     * Crea un @code IteradorAnimaciones@endcode al inicio de todas las animaciones de un personaje
     * determinado, identificado por su @code nombre_personaje@endcode.
     */
    IteradorAnimaciones begin_animaciones_personaje(const std::string& nombre_personaje);

    /**
     * Crea un @code IteradorAnimaciones@endcode al final de todas las animaciones de un personaje
     * determinado, identificado por su @code nombre_personaje@endcode.
     */
    IteradorAnimaciones end_animaciones_personaje(const std::string& nombre_personaje);
};

#endif  // LECTOR_TEXTURAS_H
