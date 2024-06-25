#ifndef ADMIN_RECOGIBLES_H
#define ADMIN_RECOGIBLES_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_recogible.h"

#include "camara.h"
#include "lector_texturas.h"
#include "objeto_animado.h"

/**
 * @class AdminRecogibles
 * @brief Clase encargada de administrar la vista de todos los objetos recogibles presentes en el
 * juego.
 */
class AdminRecogibles {
private:
    static const std::unordered_map<TipoRecogible, const std::string> MAPA_TIPO_RECOGIBLE;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::vector<ObjetoAnimado> recogibles;

    /**
     * @brief Corrige el desfase entre el sprite del objeto recogible y las dimensiones del objeto
     * recogible en la lógica del juego, de forma que el sprite se dibuje correctamente
     * @param coords_sprite Coordenadas del sprite
     * @param dimensiones Dimensiones y coordenadas del objeto recogible en la lógica del juego
     * @return Dimensiones con las coordenadas corregidas
     */
    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              const SDL2pp::Rect& dimensiones);

public:
    AdminRecogibles(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminRecogibles(const AdminRecogibles&) = delete;
    AdminRecogibles& operator=(const AdminRecogibles&) = delete;

    /**
     * @brief Elimina todos los objetos recogibles del juego.
     */
    void eliminar_recogibles();

    /**
     * @brief Agrega un objeto recogible al juego
     * @param tipo_recogible Tipo de objeto recogible
     * @param dimensiones Dimensiones del objeto recogible en la lógica del juego.
     */
    void agregar_recogible(TipoRecogible tipo_recogible, const SDL2pp::Rect& dimensiones);

    /**
     * @brief Dibuja todos los objetos recogibles
     */
    void dibujar_recogibles() const;

    ~AdminRecogibles();
};

#endif  // ADMIN_RECOGIBLES_H
