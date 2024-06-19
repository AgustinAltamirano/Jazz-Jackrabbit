#include "hud.h"

#include <utility>

#include "vista_juego_defs.h"

#define CORAZON "corazon"
#define INFINITO "infinito"

#define TITULO_TOP "TOP JUGADORES"

const std::unordered_map<TipoArma, std::string> HUD::MAPA_TIPO_ARMA{
        {INFINITA, "infinita"},
        {ARMA1, "arma1"},
        {ARMA2, "arma2"},
        {ARMA3, "arma3"},
};

const std::unordered_map<TipoPersonaje, std::string> HUD::MAPA_TIPO_PERSONAJE{
        {JAZZ, "jazz"},
        {SPAZ, "spaz"},
        {LORI, "lori"},
};

void HUD::dibujar_numero(uint32_t numero, int& pos_x, const int pos_y,
                         const bool comenzar_desde_derecha) const {
    std::vector<uint8_t> cifras;
    if (numero == 0) {
        cifras.push_back(0);
    }
    while (numero > 0) {
        cifras.push_back(static_cast<uint8_t>(numero % 10));
        numero /= 10;
    }
    SDL2pp::Texture& textura_numeros = lector_texturas.obtener_textura_fuente();
    const std::vector<SDL2pp::Rect>& coords_numeros = lector_texturas.obtener_coords_numeros();

    if (!comenzar_desde_derecha) {
        std::reverse(cifras.begin(), cifras.end());
    }

    for (const auto cifra: cifras) {
        if (comenzar_desde_derecha) {
            pos_x -= coords_numeros.at(cifra).GetW() + SEPARACION_ENTRE_NUMEROS;
        }
        renderer.Copy(textura_numeros, lector_texturas.obtener_coords_numeros().at(cifra),
                      SDL2pp::Rect(pos_x, pos_y, coords_numeros.at(cifra).GetW(),
                                   coords_numeros.at(cifra).GetH()));
        if (!comenzar_desde_derecha) {
            pos_x += coords_numeros.at(cifra).GetW() + SEPARACION_ENTRE_NUMEROS;
        }
    }
}

void HUD::dibujar_texto(const std::string& texto, int& pos_x, const int pos_y) const {
    SDL2pp::Texture& textura_letras = lector_texturas.obtener_textura_fuente();

    for (const auto& letra: texto) {
        const SDL2pp::Rect& coords_letra = lector_texturas.obtener_coords_letra(letra);
        renderer.Copy(textura_letras, coords_letra,
                      SDL2pp::Rect(pos_x, pos_y, coords_letra.GetW(), coords_letra.GetH()));
        pos_x += coords_letra.GetW() + SEPARACION_ENTRE_NUMEROS;
    }
}

void HUD::dibujar_puntos() const {
    int pos_x = POS_PUNTOS_X;
    dibujar_numero(puntos, pos_x, POS_PUNTOS_Y);
}

void HUD::dibujar_vida() const {
    int posicion_actual = POS_VIDA_X;
    SDL2pp::Texture& textura_items = lector_texturas.obtener_textura_items();
    const SDL2pp::Rect& coords_corazon = lector_texturas.obtener_coords_icono(CORAZON);
    renderer.Copy(textura_items, coords_corazon,
                  SDL2pp::Rect(posicion_actual, POS_VIDA_Y, coords_corazon.GetW(),
                               coords_corazon.GetH()));
    posicion_actual += coords_corazon.GetW() + SEPARACION_ENTRE_NUMEROS;
    dibujar_numero(vida, posicion_actual, POS_VIDA_Y);
}

void HUD::dibujar_arma() const {
    int posicion_actual = POS_ARMA_ACTUAL_X;
    SDL2pp::Texture& textura_items = lector_texturas.obtener_textura_items();
    const std::unordered_map<std::string, SDL2pp::Rect>& coords_armas =
            lector_texturas.obtener_coords_armas();
    renderer.Copy(textura_items, coords_armas.at(MAPA_TIPO_ARMA.at(arma_actual)),
                  SDL2pp::Rect(posicion_actual, POS_ARMA_ACTUAL_Y,
                               coords_armas.at(MAPA_TIPO_ARMA.at(arma_actual)).GetW(),
                               coords_armas.at(MAPA_TIPO_ARMA.at(arma_actual)).GetH()));
    posicion_actual +=
            coords_armas.at(MAPA_TIPO_ARMA.at(arma_actual)).GetW() + SEPARACION_ENTRE_NUMEROS;
    if (balas_restantes < 0) {
        SDL2pp::Texture& textura_fuente = lector_texturas.obtener_textura_fuente();
        const SDL2pp::Rect& coords_infinito = lector_texturas.obtener_coords_simbolo(INFINITO);
        renderer.Copy(textura_fuente, coords_infinito,
                      SDL2pp::Rect(posicion_actual, POS_ARMA_ACTUAL_Y, coords_infinito.GetW(),
                                   coords_infinito.GetH()));
        return;
    }
    dibujar_numero(balas_restantes, posicion_actual, POS_ARMA_ACTUAL_Y);
}

void HUD::dibujar_id_jugador() const {
    int posicion_actual = POS_ID_JUGADOR_X;
    SDL2pp::Texture& textura_jugadores =
            lector_texturas.obtener_textura_personaje(MAPA_TIPO_PERSONAJE.at(tipo_personaje));
    const SDL2pp::Rect& coords_icono =
            lector_texturas.obtener_coords_icono(MAPA_TIPO_PERSONAJE.at(tipo_personaje));
    renderer.Copy(textura_jugadores, coords_icono,
                  SDL2pp::Rect(posicion_actual - coords_icono.GetW(), POS_ID_JUGADOR_Y,
                               coords_icono.GetW(), coords_icono.GetH()));
    posicion_actual -= coords_icono.GetW();
    // Se suma 1 para que los números de jugadores comiencen en 1
    dibujar_numero(id_jugador + 1, posicion_actual, POS_ID_JUGADOR_Y, true);
}

void HUD::dibujar_top_jugadores() {
    int pos_x = POS_TITULO_TOP_JUGADORES_X;
    int pos_y = POS_TITULO_TOP_JUGADORES_Y;

    dibujar_texto(TITULO_TOP, pos_x, pos_y);

    pos_x = POS_TOP_JUGADORES_X;
    pos_y = POS_TOP_JUGADORES_Y;

    const auto jugadores = top_jugadores.obtener_top_jugadores(false);

    for (const auto& [id, puntaje, tipo]: jugadores) {
        SDL2pp::Texture& textura_jugadores =
                lector_texturas.obtener_textura_personaje(MAPA_TIPO_PERSONAJE.at(tipo));
        const SDL2pp::Rect& coords_icono =
                lector_texturas.obtener_coords_icono(MAPA_TIPO_PERSONAJE.at(tipo));
        renderer.Copy(textura_jugadores, coords_icono,
                      SDL2pp::Rect(pos_x, pos_y, coords_icono.GetW(), coords_icono.GetH()));
        pos_x += coords_icono.GetW() + SEPARACION_ENTRE_NUMEROS;
        dibujar_numero(id + 1, pos_x, pos_y);
        pos_x = POS_PUNTAJES_JUGADORES_X;
        dibujar_numero(puntaje, pos_x, pos_y);
        pos_x = POS_TOP_JUGADORES_X;
        pos_y += coords_icono.GetH() + SEPARACION_VERTICAL_TOP;
    }
}

HUD::HUD(const int32_t id_jugador, SDL2pp::Renderer& renderer, LectorTexturas& lector_texturas):
        renderer(renderer),
        lector_texturas(lector_texturas),
        id_jugador(id_jugador),
        tipo_personaje(JAZZ),
        puntos(0),
        vida(0),
        arma_actual(INFINITA),
        balas_restantes(-1) {}

void HUD::actualizar(const TipoPersonaje tipo_personaje, const uint32_t puntos, const uint32_t vida,
                     const TipoArma arma_actual, const int32_t balas_restantes) {
    this->tipo_personaje = tipo_personaje;
    this->puntos = puntos;
    this->vida = vida;
    this->arma_actual = arma_actual;
    this->balas_restantes = balas_restantes;
}

void HUD::actualizar_top_jugadores(
        std::vector<std::tuple<int32_t, uint32_t, TipoPersonaje>>&& jugadores) {
    top_jugadores.actualizar_jugadores(std::move(jugadores));
}

void HUD::dibujar(const bool mostrar_top) {
    dibujar_puntos();
    dibujar_vida();
    dibujar_arma();
    dibujar_id_jugador();
    if (mostrar_top) {
        dibujar_top_jugadores();
    }
}

HUD::~HUD() = default;
