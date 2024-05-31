#include "boton_animado_jugador.h"

#include "constantes_menu.h"


BotonAnimadoJugador::BotonAnimadoJugador(QMainWindow* parent, int num_sprite, int ancho, int alto):
        BotonMenu(parent, 0, 0, ANCHO_PANTALLA, ALTO_PANTALLA, ""),
        label_jugador(this),
        label_nombre(this),
        manejador_sprites(label_jugador, label_nombre, num_sprite, ancho, alto) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
}


void BotonAnimadoJugador::paintEvent(QPaintEvent* event) {
    manejador_sprites.pintar_frame_actual();
}


void BotonAnimadoJugador::focusInEvent(QFocusEvent* event) {
    manejador_sprites.animacion_hacia_adelante();
    clicked();
    BotonMenu::focusInEvent(event);
}


void BotonAnimadoJugador::focusOutEvent(QFocusEvent* event) {
    manejador_sprites.animacion_en_reversa();
    QPushButton::focusOutEvent(
            event);  // Llama a la implementación base para mantener el comportamiento normal
}
