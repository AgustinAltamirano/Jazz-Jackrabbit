#include "lista_botones.h"

#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QVariant>
#include <iostream>

#include "constantes.h"
#include "escena_editor.h"


ListaBotones::ListaBotones(QWidget* parent, QGraphicsView& vista_escena, EscenaEditor& escena) :
        QVBoxLayout(parent),
        items(),
        botones_por_mapa(),
        tipo_item_seleccionado(),
        escena(escena),
        vista_escena(vista_escena) {}


void ListaBotones::inicializar_boton_item(QPixmap& imagen_item,
                                          const std::string& tipo_item,
                                          const std::string& mapa_asociado,
                                          int posicion) {
    auto boton_item = crear_boton(imagen_item, tipo_item);
    boton_item->setProperty("posicion", posicion);

    connect(boton_item.get(), &QPushButton::clicked, this, &ListaBotones::seleccionar_item);

    if (not mapa_asociado.empty()) {
        boton_item->hide();
        addWidget(boton_item.get());
        botones_por_mapa[mapa_asociado].emplace_back(std::move(boton_item));
        items_por_mapa[tipo_item] = mapa_asociado;
    } else {
        addWidget(boton_item.release());
    }
}


std::unique_ptr<QPushButton> ListaBotones::crear_boton(QPixmap& imagen_item, const std::string& tipo_item) {
    auto boton_item = std::make_unique<QPushButton>();
    boton_item->setIcon(QIcon(imagen_item));
    boton_item->setIconSize(QSize(TAM_ITEM, TAM_ITEM));
    boton_item->setProperty("tipo", tipo_item.c_str());
    boton_item->setStyleSheet("QPushButton {border: none; background: none;}");
    items.emplace(tipo_item, imagen_item);
    return boton_item;
}


void ListaBotones::inicializar_boton_texturas(QPixmap& imagen_fondo, const std::string& nombre_mapa) {
    auto boton_escenario = crear_boton(imagen_fondo, nombre_mapa);
    connect(boton_escenario.get(), &QPushButton::clicked, this, &ListaBotones::seleccionar_texturas);
    addWidget(boton_escenario.release());
}


void ListaBotones::seleccionar_texturas() {
    auto boton_textura = qobject_cast<QPushButton*>(sender());
    auto tipo_textura_mapa = boton_textura->property("tipo").toString().toStdString();

    QPixmap imagen_recortada = items[tipo_textura_mapa];
    QBrush brush(imagen_recortada);

    vista_escena.setBackgroundBrush(brush);

    for (const auto& mapa_actual: botones_por_mapa) {
        auto tipo_mapa = mapa_actual.first;

        for (const auto& boton_actual: mapa_actual.second) {
            if (tipo_mapa != tipo_textura_mapa) {
                boton_actual->hide();
            } else {
                int posicion_en_layout = boton_actual->property("posicion").toInt();
                itemAt(posicion_en_layout)->widget()->show();
            }
        }
    }

    escena.actualizar_texturas(tipo_textura_mapa);
}


void ListaBotones::seleccionar_item() {
    auto boton = qobject_cast<QPushButton*>(sender());
    tipo_item_seleccionado = boton->property("tipo").toString().toStdString();
}


QPixmap& ListaBotones::obtener_imagen_item_seleccionado() {
    return items[tipo_item_seleccionado];
}


std::string ListaBotones::obtener_tipo_item_seleccionado() {
    return tipo_item_seleccionado;
}


QPixmap& ListaBotones::obtener_imagen_item(const std::string& tipo_item) {
    return items[tipo_item];
}


std::string ListaBotones::obtener_mapa_item(const std::string& tipo_item) {
    return items_por_mapa[tipo_item];
}
