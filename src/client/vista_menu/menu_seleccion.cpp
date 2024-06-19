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
        volver_menu_previo();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}


void MenuSeleccion::realizar_accion_clic() {
    auto boton_clickeado = qobject_cast<QPushButton*>(sender());
    boton_clickeado->clearFocus();
    enfocar(boton_clickeado);
    realizar_accion_menu(boton_clickeado);
}


void MenuSeleccion::conectar_botones(const std::vector<QPushButton*>& botones,
                                     const std::vector<int>& props, QBoxLayout& layout) {
    // Defino los handlers  y propiedades de los botones
    for (int i = 0; i < botones.size(); i++) {
        auto* boton = botones[i];

        connect(boton, &QPushButton::clicked, this,
                &MenuSeleccion::realizar_accion_clic);

        boton->setProperty(KEY_TIPO_BOTON, QVariant(props[i]));

        layout.addWidget(boton);
    }
}


void MenuSeleccion::volver_menu_previo() {
    desenfocar_boton();
    menu_previo->move(this->pos());
    menu_previo->show();
    hide();
}


void MenuSeleccion::enfocar(QPushButton* boton) {
    boton_enfocado = boton;
}


void MenuSeleccion::desenfocar_boton() {
    if (boton_enfocado != nullptr) {
        boton_enfocado->clearFocus();
        boton_enfocado = nullptr;
    }
}
