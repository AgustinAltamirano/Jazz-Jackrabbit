#include "lista_botones.h"

#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QVariant>
#include <iostream>

#include "constantes.h"
#include "escena_editor.h"
#include "main_window.h"


ListaBotones::ListaBotones(QWidget* parent, EscenaEditor& escena) :
        QVBoxLayout(parent),
        items(),
        tipo_item_seleccionado(),
        escenario(),
        escena(escena) {}


void ListaBotones::inicializar_boton_item(ItemEscena item, int posicion) {
    auto mapa_asociado = item.mapa_asociado;
    escenario = mapa_asociado;

    auto boton_item = crear_boton(std::move(item));
    boton_item->setProperty(KEY_POSICION_BTN, posicion);
    connect(boton_item, &QPushButton::clicked, this, &ListaBotones::seleccionar_item);

    if (not mapa_asociado.empty()) {
        boton_item->hide();
        addWidget(boton_item);
    } else {
        addWidget(boton_item);
    }
}


QPushButton* ListaBotones::crear_boton(ItemEscena item) {
    auto boton_item = new QPushButton(this->parentWidget());
    boton_item->setIcon(QIcon(item.imagen));
    boton_item->setIconSize(QSize(TAM_ITEM, TAM_ITEM));
    boton_item->setProperty(KEY_TIPO_BTN, item.tipo.c_str());
    boton_item->setStyleSheet("QPushButton {border: none; background: none;}");
    boton_item->setProperty(KEY_MAPA_BTN, item.mapa_asociado.c_str());
    items.emplace(item.tipo.c_str(), std::move(item));
    return boton_item;
}


void ListaBotones::inicializar_boton_texturas(ItemEscena item) {
    auto boton_escenario = crear_boton(std::move(item));
    connect(boton_escenario, &QPushButton::clicked, this, &ListaBotones::seleccionar_texturas);
    addWidget(boton_escenario);
}


void ListaBotones::seleccionar_texturas() {
    auto boton_escenario = qobject_cast<QPushButton*>(sender());
    auto mapa_seleccionado = boton_escenario->property(KEY_TIPO_BTN).toString().toStdString();

    for (int i = 1; i < count(); ++i) {
        auto item_layout = itemAt(i);
        auto boton_bloque = qobject_cast<QPushButton*>(item_layout->widget());
        auto mapa_actual = boton_bloque->property(KEY_MAPA_BTN).toString().toStdString();

        if (not mapa_actual.empty() && mapa_actual != mapa_seleccionado) {
            boton_bloque->hide();
        } else {
            boton_bloque->show();
        }
    }

    escena.actualizar_texturas(mapa_seleccionado);
    escenario = mapa_seleccionado;
}


void ListaBotones::seleccionar_item() {
    auto boton = qobject_cast<QPushButton*>(sender());
    tipo_item_seleccionado = boton->property(KEY_TIPO_BTN).toString().toStdString();
}


std::unique_ptr<QGraphicsPixmapItem> ListaBotones::obtener_item_seleccionado() {
    auto item = items[tipo_item_seleccionado];
    auto bloque_item = std::make_unique<QGraphicsPixmapItem>(item.imagen);
    bloque_item.get()->setData(KEY_TIPO_ITEM, QVariant(tipo_item_seleccionado.c_str()));

    if (not item.mapa_asociado.empty()) {
        bloque_item.get()->setData(KEY_MAPA_ASOCIADO, QVariant(item.mapa_asociado.c_str()));
    }

    return std::move(bloque_item);
}


std::string ListaBotones::obtener_tipo_item_seleccionado() {
    return tipo_item_seleccionado;
}


QPixmap& ListaBotones::obtener_imagen_item(const std::string& tipo_item) {
    return items[tipo_item].imagen;
}


void ListaBotones::actualizar_tipo_item_seleccionado(const std::string& nuevo_tipo_item) {
    tipo_item_seleccionado = nuevo_tipo_item;
}


std::string ListaBotones::obtener_escenario() {
    return escenario;
}
