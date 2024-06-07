#include "lista_botones.h"

#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QVariant>
#include <iostream>

#include "constantes.h"
#include "escena_editor.h"
#include "main_window.h"


ListaBotones::ListaBotones(QWidget* parent, EscenaEditor& escena) :
        QVBoxLayout(parent), items(), item_seleccionado(),
        escenario(ESCENARIO1),
        escena(escena) {}


void ListaBotones::inicializar_boton_item(ItemEscena item, int posicion) {
    auto mapa_asociado = item.mapa_asociado;
    escenario = mapa_asociado;

    auto boton_item = crear_boton(std::move(item));
    boton_item->setProperty(KEY_POSICION_BTN, posicion);
    connect(boton_item, &QPushButton::clicked, this, &ListaBotones::seleccionar_item);

    if (mapa_asociado != ESCENARIO_INDEFINIDO) {
        boton_item->hide();
        addWidget(boton_item);
    } else {
        addWidget(boton_item);
    }
}


void ListaBotones::inicializar_boton_texturas(ItemEscena item) {
    auto boton_escenario = crear_boton(std::move(item));
    connect(boton_escenario, &QPushButton::clicked, this, &ListaBotones::seleccionar_texturas);
    addWidget(boton_escenario);
}


QPushButton* ListaBotones::crear_boton(ItemEscena item) {
    auto boton_item = new QPushButton(this->parentWidget());
    boton_item->setIcon(QIcon(item.imagen));
    boton_item->setIconSize(QSize(TAM_ITEM, TAM_ITEM));
    boton_item->setProperty(KEY_TIPO_BTN, item.tipo);
    boton_item->setStyleSheet("QPushButton {border: none; background: none;}");
    boton_item->setProperty(KEY_MAPA_BTN, item.mapa_asociado);
    items.emplace(std::make_pair(item.tipo, item.mapa_asociado), std::move(item));
    return boton_item;
}


void ListaBotones::seleccionar_texturas() {
    auto boton_escenario = qobject_cast<QPushButton*>(sender());
    auto mapa_seleccionado = boton_escenario->property(KEY_MAPA_BTN).value<TipoEscenarioEditor>();

    for (int i = 1; i < count(); ++i) {
        auto item_layout = itemAt(i);
        auto boton_bloque = qobject_cast<QPushButton*>(item_layout->widget());
        auto tipo_bloque = boton_bloque->property(KEY_TIPO_BTN).value<TipoItemEditor>();
        auto mapa_actual = boton_bloque->property(KEY_MAPA_BTN).value<TipoEscenarioEditor>();

        if (mapa_actual == ESCENARIO_INDEFINIDO || tipo_bloque == TEXTURA || mapa_actual == mapa_seleccionado) {
            boton_bloque->show();
        } else {
            boton_bloque->hide();
        }
    }

    escenario = mapa_seleccionado;
    escena.actualizar_texturas(mapa_seleccionado);
}


void ListaBotones::seleccionar_item() {
    auto boton = qobject_cast<QPushButton*>(sender());
    auto tipo_item = boton->property(KEY_TIPO_BTN).value<TipoItemEditor>();
    auto mapa_asociado = boton->property(KEY_MAPA_BTN).value<TipoEscenarioEditor>();
    item_seleccionado = items.at(std::make_pair(tipo_item, mapa_asociado));
}

std::unique_ptr<QGraphicsPixmapItem> ListaBotones::obtener_item_seleccionado() const {
    auto tipo_item = item_seleccionado.tipo;
    auto mapa_asociado = item_seleccionado.mapa_asociado;
    auto imagen = item_seleccionado.imagen;

    auto bloque_item = std::make_unique<QGraphicsPixmapItem>(imagen);
    bloque_item.get()->setData(KEY_TIPO_ITEM, QVariant(tipo_item));

    if (mapa_asociado != ESCENARIO_INDEFINIDO) {
        bloque_item.get()->setData(KEY_MAPA_ASOCIADO, QVariant(mapa_asociado));
    }
    return std::move(bloque_item);
}


QPixmap& ListaBotones::obtener_imagen_item(TipoItemEditor tipo,
                                            TipoEscenarioEditor texturas) {
    return items[std::make_pair(tipo, texturas)].imagen;
}


ItemEscena& ListaBotones::obtener_item(TipoItemEditor tipo, TipoEscenarioEditor texturas) {
    return items[std::make_pair(tipo, texturas)];
}


TipoEscenarioEditor ListaBotones::obtener_escenario() {
    return escenario;
}


void ListaBotones::actualizar_item_seleccionado(const ItemEscena& nuevo_item) {
    item_seleccionado = nuevo_item;
}
