#include "menu_seleccion.h"

#include <QBoxLayout>

#include "constantes_menu.h"


MenuSeleccion::MenuSeleccion(QMainWindow* parent):
        QMainWindow(parent),
        menu_previo(parent) {
    setWindowTitle(TITULO_VENTANAS);
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
}


void MenuSeleccion::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        boton_enfocado = nullptr;
        menu_previo->move(this->pos());
        menu_previo->show();
        hide();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}


void MenuSeleccion::realizar_accion_clic() {
    auto* boton_clickeado = dynamic_cast<QPushButton*>(sender());
    if (boton_clickeado == boton_enfocado) {
        boton_enfocado = nullptr;

        int boton_seleccionado = boton_clickeado->property(KEY_TIPO_BOTON).toInt();
        realizar_accion_menu(boton_seleccionado);
        return;
    }
    boton_enfocado = boton_clickeado;
}


void MenuSeleccion::conectar_botones(const std::vector<QPushButton*>& botones,
                                     const std::vector<int>& props, QBoxLayout& layout) {
    // Defino los handlers  y propiedades de los botones
    for (int i = 0; i < botones.size(); i++) {
        auto* boton = botones[i];

        connect(boton, &QPushButton::clicked, this,
                &MenuSeleccion::realizar_accion_clic);

        boton->setProperty(KEY_TIPO_BOTON, props[i]);

        layout.addWidget(boton);
    }
}
