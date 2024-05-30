#include "boton_animado.h"

#include "constantes_menu.h"


BotonAnimado::BotonAnimado(QMainWindow* parent, int num_sprite, int ancho, int alto):
        BotonMenu(parent, 0, 0, ANCHO_PANTALLA, ALTO_PANTALLA, ""),
        label_jugador(this),
        label_nombre(this),
        manejador_texturas(label_jugador, label_nombre, num_sprite, ancho, alto) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
}


void BotonAnimado::paintEvent(QPaintEvent* event) {
    manejador_texturas.pintar_frame_boton();
    manejador_texturas.pintar_frame_nombre();
}


void BotonAnimado::focusInEvent(QFocusEvent* event) {
    manejador_texturas.animacion_hacia_adelante();
    clicked();
    BotonMenu::focusInEvent(event);
}


void BotonAnimado::focusOutEvent(QFocusEvent* event) {
    manejador_texturas.animacion_en_reversa();
    QPushButton::focusOutEvent(
            event);  // Llama a la implementación base para mantener el comportamiento normal
}
