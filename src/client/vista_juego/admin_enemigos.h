#ifndef ADMIN_ENEMIGOS_H
#define ADMIN_ENEMIGOS_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_enemigo.h"

#include "camara.h"
#include "lector_texturas.h"
#include "objeto_animado.h"

// Si no se actualiza un enemigo en esta cantidad de iteraciones, se elimina de la vista.
#define ITERACIONES_HASTA_ELIMINAR 3

/**
 * @class AdminEnemigos
 * @brief Clase encargada de administrar la vista de todos los enemigos presentes en el juego.
 */
class AdminEnemigos {
private:
    static const std::unordered_map<TipoEnemigo, const std::string> MAPA_TIPO_ENEMIGO;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::unordered_map<uint32_t, ObjetoAnimado> enemigos;

    /** Mapa que indica los enemigos que ya no se encuentran presentes en el juego y
     * deben ser eliminados en futuras iteraciones. Cada id tiene asociado el número de iteraciones
     * que deben transcurrir hasta ser eliminado. Cuando este número llega a cero, se elimina.
     */
    std::unordered_map<uint32_t, int> contador_enemigos;

    /**
     * @brief Corrige el desfase entre el sprite del enemigo y las coordenadas del enemigo en la
     * lógica del juego, de forma que el sprite se dibuje correctamente.
     * @param id_enemigo ID del enemigo
     * @param dimensiones Dimensiones y coordenadas del enemigo en la lógica del juego
     * @param invertido Indica si el sprite debe dibujarse invertido horizontalmente
     * @return Dimensiones con las coordenadas corregidas
     */
    SDL2pp::Rect corregir_desfase_sprite(uint32_t id_enemigo, const SDL2pp::Rect& dimensiones,
                                         bool invertido) const;

public:
    AdminEnemigos(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminEnemigos(const AdminEnemigos&) = delete;

    AdminEnemigos& operator=(const AdminEnemigos&) = delete;

    /**
     * @brief Verifica si existe un enemigo en el juego
     * @param id_enemigo ID del enemigo
     * @return Verdadero si el enemigo existe, falso en caso contrario
     */
    bool existe_enemigo(uint32_t id_enemigo) const;

    /**
     * @brief Agrega un enemigo al juego
     * @param id_enemigo ID del enemigo
     * @param tipo Tipo de enemigo
     * @param dimensiones_iniciales Coordenadas iniciales del enemigo en la lógica del juego. Los
     * valores de ancho y alto del rectángulo representan el factor de escala con el que se desea
     * dibujar al enemigo respecto del tamaño original del sprite.
     * @param invertido Indica si el sprite debe dibujarse invertido horizontalmente
     */
    void agregar_enemigo(int32_t id_enemigo, TipoEnemigo tipo, SDL2pp::Rect dimensiones_iniciales,
                         bool invertido);

    /**
     * @brief Actualiza la animación de un enemigo
     * @param id_enemigo ID del enemigo
     * @param iteraciones_actuales Número de iteraciones actuales del juego
     * @param dimensiones Dimensiones actuales del enemigo en la lógica del juego
     * @param invertido Indica si el sprite debe dibujarse invertido horizontalmente
     */
    void actualizar_animacion(uint32_t id_enemigo, uint32_t iteraciones_actuales,
                              const SDL2pp::Rect& dimensiones, bool invertido);

    /**
     * @brief Dibuja todos los enemigos presentes en el juego
     */
    void dibujar_enemigos();

    ~AdminEnemigos();
};

#endif  // ADMIN_ENEMIGOS_H
