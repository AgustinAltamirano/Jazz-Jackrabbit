#ifndef ADMIN_BALAS_H
#define ADMIN_BALAS_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/tipo_arma.h"

#include "camara.h"
#include "lector_texturas.h"
#include "objeto_animado.h"

/**
 * @Class AdminBalas
 * @brief Clase encargada de administrar la vista de todas las balas presentes en el juego.
 */
class AdminBalas {
private:
    static const std::unordered_map<TipoArma, const std::string> MAPA_TIPO_ARMA;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::vector<ObjetoAnimado> balas;

    /**
     * @brief Corrige el desfase entre el sprite de la bala y las coordenadas de la bala en la
     * lógica del juego, de forma que el sprite se dibuje centrado respecto a esas coordenadas.
     * @param coords_sprite Dimensiones y coordenadas del sprite
     * @param pos_x Posición x de la bala en la lógica de juego
     * @param pos_y Posición y de la bala en la lógica de juego
     * @return Dimensiones con las coordenadas corregidas
     */
    [[nodiscard]] static SDL2pp::Rect corregir_desfase_sprite(const SDL2pp::Rect& coords_sprite,
                                                              int32_t pos_x, int32_t pos_y);

public:
    AdminBalas(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminBalas(const AdminBalas&) = delete;
    AdminBalas& operator=(const AdminBalas&) = delete;

    /** Elimina todas las balas presentes en el juego. */
    void eliminar_balas();

    /**
     * @brief Agrega una bala al juego.
     * @param tipo_arma Tipo de arma de la bala
     * @param pos_x Posición x de la bala
     * @param pos_y Posición y de la bala
     */
    void agregar_bala(TipoArma tipo_arma, int32_t pos_x, int32_t pos_y);

    /**
     * @brief Dibuja todas las balas
     */
    void dibujar_balas() const;

    ~AdminBalas();
};

#endif  // ADMIN_BALAS_H
