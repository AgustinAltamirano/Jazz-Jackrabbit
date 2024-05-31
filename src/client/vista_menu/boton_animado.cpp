#include "boton_animado.h"

#include "constantes_menu.h"


BotonAnimado::BotonAnimado(QMainWindow* parent, int num_sprite, int ancho, int alto):
        BotonMenu(parent, 0, 0, ANCHO_PANTALLA, ALTO_PANTALLA, ""),
        label_jugador(this),
        label_nombre(this),
        manejador_sprites(label_jugador, label_nombre, num_sprite, ancho, alto) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
}


void BotonAnimado::paintEvent(QPaintEvent* event) {
    manejador_sprites.pintar_frame_actual();
}


void BotonAnimado::focusInEvent(QFocusEvent* event) {
    manejador_sprites.animacion_hacia_adelante();
    clicked();
    BotonMenu::focusInEvent(event);
}


void BotonAnimado::focusOutEvent(QFocusEvent* event) {
    manejador_sprites.animacion_en_reversa();
    QPushButton::focusOutEvent(
            event);  // Llama a la implementación base para mantener el comportamiento normal
}
