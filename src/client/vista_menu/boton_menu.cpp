#include "boton_menu.h"

#include <random>

#include "ventana_inicial.h"


BotonMenu::BotonMenu(QWidget* parent, int offset_x, int offset_y, int ancho, int alto,
                     const char* text):
        QPushButton(parent), reproductor_efectos(), efectos_de_sonido() {
    setGeometry(QRect(offset_x, offset_y, ancho, alto));
    QFont fuente = obtener_fuente();
    fuente.setPointSize(TAMANIO_FUENTE_BTN);
    setFont(fuente);

    QString estilo = QString("QPushButton { border: none; background: none; color : %1;}"
                             "QPushButton:focus { color: %2; outline: none; }")
                             .arg(RGB_BTN, RGB_HOVER_BTN);
    setStyleSheet(estilo);
    setText(text);
    setMouseTracking(true);
    definir_efectos_de_sonido();
}


void BotonMenu::definir_efectos_de_sonido() {
    for (int i = 0; i <= CANT_EFECTOS_SONIDO; ++i) {
        auto url = QUrl::fromLocalFile(QString(ASSETS_PATH) + RUTA_EFECTOS_SONIDO + QString::number(i) + EXTENSION_EFECTOS_SONIDO);
        efectos_de_sonido.addMedia(url);
    }
    efectos_de_sonido.setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    reproductor_efectos.setPlaylist(&efectos_de_sonido);
    reproductor_efectos.setVolume(VOLUMEN_EFECTOS_SONIDO);
}


void BotonMenu::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        clicked();
    } else {
        QPushButton::keyPressEvent(event);  // Propaga el evento al manejador por defecto
    }
}


void BotonMenu::mouseMoveEvent(QMouseEvent* event) {
    setFocus();  // Pone el foco en el botón cuando el mouse se mueve sobre él
    QPushButton::mouseMoveEvent(
            event);  // Llama al método original para que el botón funcione normalmente
}


void BotonMenu::focusInEvent(QFocusEvent* event) {
    reproducir_efecto_sonido();
    QPushButton::focusInEvent(
            event);  // Llama al método original para que el botón funcione normalmente
}


void BotonMenu::reproducir_efecto_sonido() {
    // Crea un generador de números aleatorios y elige uno
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, efectos_de_sonido.mediaCount() - 1);
    int random_num = distr(gen);

    efectos_de_sonido.setCurrentIndex(random_num);
    reproductor_efectos.play();
}
