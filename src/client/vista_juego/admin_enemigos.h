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

class AdminEnemigos {
private:
    static const std::unordered_map<TipoEnemigo, const std::string> MAPA_TIPO_ENEMIGO;

    SDL2pp::Renderer& renderer;
    LectorTexturas& lector_texturas;
    Camara& camara;
    std::unordered_map<uint32_t, ObjetoAnimado> enemigos;

    /** Set que indica los enemigos que ya no se encuentran presentes en el juego y
     * deben ser eliminados.
     */
    std::unordered_set<uint32_t> ids_enemigos_a_eliminar;

    SDL2pp::Rect corregir_desfase_sprite(uint32_t id_enemigo, const SDL2pp::Rect& dimensiones,
                                         bool invertido) const;

public:
    AdminEnemigos(SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas, Camara& camara);

    AdminEnemigos(const AdminEnemigos&) = delete;

    AdminEnemigos& operator=(const AdminEnemigos&) = delete;

    bool existe_enemigo(uint32_t id_enemigo) const;

    void agregar_enemigo(int32_t id_enemigo, TipoEnemigo tipo, SDL2pp::Rect dimensiones_iniciales,
                         bool invertido);

    void actualizar_animacion(uint32_t id_enemigo, uint32_t iteraciones_actuales,
                              const SDL2pp::Rect& dimensiones, bool invertido);

    void dibujar_enemigos();

    ~AdminEnemigos();
};

#endif  // ADMIN_ENEMIGOS_H
