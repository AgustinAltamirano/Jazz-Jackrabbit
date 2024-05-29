#include "boton_animado.h"
#include "constantes_menu.h"


BotonAnimado::BotonAnimado(QMainWindow* parent, int num_personaje, int ancho, int alto) :
        QPushButton(parent),
        label_jugador(this),
        label_nombre(this),
        manejador_texturas(label_jugador, label_nombre, num_personaje, ancho, alto) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    label_jugador.installEventFilter(this);
    label_nombre.installEventFilter(this);
}


void BotonAnimado::paintEvent(QPaintEvent* event) {
    manejador_texturas.pintar_frame_jugador();
    manejador_texturas.pintar_frame_nombre();
}


void BotonAnimado::focusInEvent(QFocusEvent* event) {
    manejador_texturas.animacion_hacia_adelante();
    clicked();
    QPushButton::focusInEvent(event); // Llama a la implementación base para mantener el comportamiento normal
}


void BotonAnimado::focusOutEvent(QFocusEvent* event) {
    manejador_texturas.animacion_en_reversa();
    QPushButton::focusOutEvent(event); // Llama a la implementación base para mantener el comportamiento normal
}


void BotonAnimado::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        clicked();
    } else {
        QPushButton::keyPressEvent(event);  // Propaga el evento al manejador por defecto
    }
}


void BotonAnimado::mouseMoveEvent(QMouseEvent *event) {
    setFocus();                 // Pone el foco en el botón cuando el mouse se mueve sobre él
    QPushButton::mouseMoveEvent(event);  // Llama al método original para que el botón funcione normalmente
}


bool BotonAnimado::eventFilter(QObject* watched, QEvent* event) {
    if (watched == &label_jugador && event->type() == QEvent::MouseMove) {
        mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    }
    // Delega el manejo del evento a la implementación base para otros casos
    return QPushButton::eventFilter(watched, event);
}
