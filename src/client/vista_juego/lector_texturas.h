#ifndef LECTOR_TEXTURAS_H
#define LECTOR_TEXTURAS_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

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

    std::unique_ptr<SDL2pp::Texture> textura_explosion;

    std::vector<SDL2pp::Rect> coords_explosion;

    /** Carga todas las texturas y coordenadas de la pantalla de carga */
    void cargar_texturas_y_coordenadas_pantalla_carga();

    /** Carga todas las texturas y coordenadas de los escenarios y bloques */
    void cargar_texturas_y_coordenadas_escenarios();

    /** Carga todas las texturas y coordenadas de los personajes */
    void cargar_texturas_y_coordenadas_personajes();

    /** Carga todas las texturas y coordenadas de los enemigos */
    void cargar_texturas_y_coordenadas_enemigos();

    /** Carga todas las texturas y coordenadas de la fuente (números, símbolos y letras) */
    void cargar_texturas_y_coordenadas_fuente();

    /** Carga todas las texturas y coordenadas de los items e íconos */
    void cargar_texturas_y_coordenadas_items();

    /** Carga todas las texturas y coordenadas del efecto de explosión  */
    void cargar_texturas_y_coordenadas_explosion();

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

    /**
     * Obtiene la textura del fondo correspondiente al tipo de escenario.
     * @param tipo_escenario nombre del tipo de escenario
     * @return referencia a la textura del fondo de escenario
     */
    SDL2pp::Texture& obtener_textura_fondo_escenario(const std::string& tipo_escenario);

    /**
     * Obtiene las coordenadas del fondo correspondiente al tipo de escenario.
     * @param tipo_escenario nombre del tipo de escenario
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const SDL2pp::Rect& obtener_coords_fondo_escenario(const std::string& tipo_escenario) const;

    /**
     * Obtiene la textura del bloque correspondiente al tipo de escenario.
     * @param tipo_escenario nombre del tipo de escenario
     * @return referencia a la textura del bloque de escenario
     */
    SDL2pp::Texture& obtener_textura_bloque(const std::string& tipo_escenario);

    /**
     * Obtiene las coordenadas del bloque correspondiente al tipo de escenario y tipo de bloque.
     * @param tipo_escenario nombre del tipo de escenario
     * @param tipo_bloque nombre del tipo de bloque
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const SDL2pp::Rect& obtener_coords_bloque(const std::string& tipo_escenario,
                                              const std::string& tipo_bloque) const;

    /**
     * Obtiene la textura de los enemigos.
     * @return referencia a la textura de los enemigos
     */
    SDL2pp::Texture& obtener_textura_enemigos() const;

    /**
     * Obtiene las coordenadas de todos los sprites de un enemigo
     * @param enemigo nombre del enemigo
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_enemigo(const std::string& enemigo) const;

    /**
     * Obtiene la textura de la fuente (números, símbolos y letras).
     * @return referencia a la textura de la fuente
     */
    SDL2pp::Texture& obtener_textura_fuente() const;

    /**
     * Obtiene las coordenadas de todos los números.
     * @return referencia a un vector de @code SDL2pp::Rect@endcode que contiene todas las
     * coordenadas
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_numeros() const;

    /**
     * Obtiene las coordenadas de un símbolo.
     * @param nombre_simbolo nombre del símbolo
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const SDL2pp::Rect& obtener_coords_simbolo(const std::string& nombre_simbolo) const;

    /**
     * Obtiene las coordenadas de una letra.
     * @param letra letra
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const SDL2pp::Rect& obtener_coords_letra(char letra) const;

    /**
     * Obtiene la textura de los items e íconos.
     * @return referencia a la textura de los items e íconos
     */
    SDL2pp::Texture& obtener_textura_items() const;

    /**
     * Obtiene las coordenadas de un ícono.
     * @param nombre_icono nombre del ícono
     * @return referencia a un @code SDL2pp::Rect@endcode que contiene las coordenadas
     */
    const SDL2pp::Rect& obtener_coords_icono(const std::string& nombre_icono) const;

    /**
     * Obtiene las coordenadas de todas las armas del juego.
     * @return referencia a un mapa de @code SDL2pp::Rect@endcode que contiene todas las coordenadas
     */
    const std::unordered_map<std::string, SDL2pp::Rect>& obtener_coords_armas() const;

    /**
     * Obtiene las coordenadas de un tipo de bala.
     * @param nombre_arma nombre del arma correspondiente a la bala
     * @return referencia a un mapa de @code SDL2pp::Rect@endcode que contiene todas las coordenadas
     * del sprite de la bala
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_bala(const std::string& nombre_arma) const;

    /**
     * Obtiene las coordenadas del sprite de todos los objetos recogibles.
     * @param nombre_recogible nombre del objeto recogible
     * @return referencia a un vector de @code SDL2pp::Rect@endcode que contiene todas las
     * coordenadas
     */
    const std::vector<SDL2pp::Rect>& obtener_coords_recogible(
            const std::string& nombre_recogible) const;

    /**
     * Obtiene la textura del efecto de explosión.
     * @return referencia a la textura del efecto de explosión
     */
    SDL2pp::Texture& obtener_textura_explosion() const;

    /**
     * Obtiene las coordenadas de todos los sprites del efecto de explosión.
     * @return referencia a un vector de @code SDL2pp::Rect@endcode que contiene todas las
     * coordenadas
     */
    std::vector<SDL2pp::Rect>& obtener_coords_explosion();

    ~LectorTexturas();
};

#endif  // LECTOR_TEXTURAS_H
