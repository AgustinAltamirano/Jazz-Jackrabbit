#include "boton_animado_mapa.h"

#include "constantes_menu.h"


BotonAnimadoMapa::BotonAnimadoMapa(QMainWindow* parent, QWidget* widget, int num_sprite, int ancho,
                                   int alto):
        BotonMenu(parent, 0, 0, ANCHO_PANTALLA, ALTO_PANTALLA, ""),
        label_jugador(this),
        manejador_sprites(widget, label_jugador, num_sprite, ancho, alto) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
}


void BotonAnimadoMapa::paintEvent(QPaintEvent* event) { manejador_sprites.pintar_frame_actual(); }


void BotonAnimadoMapa::focusInEvent(QFocusEvent* event) {
    manejador_sprites.animacion_hacia_adelante();
    clicked();
    BotonMenu::focusInEvent(event);
}


void BotonAnimadoMapa::focusOutEvent(QFocusEvent* event) {
    manejador_sprites.animacion_en_reversa();
    QPushButton::focusOutEvent(
            event);  // Llama a la implementación base para mantener el comportamiento normal
}
