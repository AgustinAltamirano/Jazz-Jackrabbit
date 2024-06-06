#include "escena_editor.h"

#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <sstream>
#include <QScrollBar>


EscenaEditor::EscenaEditor(ListaBotones& lista_botones, QWidget* widget):
        QGraphicsScene(QRectF(0, 0, ANCHO_PANTALLA, ALTO_PANTALLA)),
        lista_botones(lista_botones),
        nivel_actual(),
        vista_escena(this, widget)
{
    vista_escena.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista_escena.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void EscenaEditor::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    mouseMoveEvent(event);
    QGraphicsScene::mousePressEvent(event);
}


void EscenaEditor::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        dibujar_bloque_item(event);
    } else if (event->buttons() & Qt::RightButton) {
        borrar_bloque_item(event);
    }
    QGraphicsScene::mouseMoveEvent(event);
}


void EscenaEditor::wheelEvent(QGraphicsSceneWheelEvent* event) {
    QRectF rect = sceneRect();

    QScrollBar* vbar = vista_escena.verticalScrollBar();
    QScrollBar* hbar = vista_escena.horizontalScrollBar();

    if (event->delta() < 0 and event->orientation() == Qt::Vertical) {
        if (vbar->value() == vbar->maximum()) {
            rect = rect.united(QRectF(0, rect.height() + TAM_ITEM, TAM_ITEM, TAM_ITEM));
            setSceneRect(rect);
        }
    } else if (event->delta() < 0 and event->orientation() == Qt::Horizontal) {
        if (hbar->value() == hbar->maximum()) {
            rect = rect.united(QRectF(rect.width() + TAM_ITEM, 0, TAM_ITEM, TAM_ITEM));
            setSceneRect(rect);
        }
    }

    QGraphicsScene::wheelEvent(event);
}


void EscenaEditor::dibujar_bloque_item(QGraphicsSceneMouseEvent* event) {
    auto imagen_item = lista_botones.obtener_imagen_item_seleccionado();
    auto item = std::make_unique<QGraphicsPixmapItem>(imagen_item);

    auto x = obtener_coordenada_bloque(event->scenePos().x());
    auto y = obtener_coordenada_bloque(event->scenePos().y());

    QRectF rect_viewport = vista_escena.mapToScene(vista_escena.viewport()->rect()).boundingRect();
    if (!rect_viewport.contains(x, y)) {
        return;
    }

    item->setPos(x, y);

    auto tipo_item = lista_botones.obtener_tipo_item_seleccionado();
    item->setData(KEY_TIPO_ITEM, QVariant(tipo_item.c_str()));

    if (lista_botones.tiene_mapa_asociado(tipo_item)) {
        item->setData(KEY_MAPA_ASOCIADO, lista_botones.obtener_mapa_item(tipo_item).c_str());
    }

    addItem(item.get());
    nivel_actual[std::make_pair(x, y)] = std::move(item);
}


void EscenaEditor::borrar_bloque_item(QGraphicsSceneMouseEvent* event) {
    auto x = obtener_coordenada_bloque(event->scenePos().x());
    auto y = obtener_coordenada_bloque(event->scenePos().y());

    auto item = nivel_actual.find(std::make_pair(x, y));
    if (item != nivel_actual.end()) {
        removeItem(item->second.get());
        nivel_actual.erase(item);
        update();
    }
}


qreal EscenaEditor::obtener_coordenada_bloque(qreal coord) {
    return static_cast<int>(std::floor(coord) / TAM_ITEM) * TAM_ITEM;
}


// Es para usar desde fuera de la clase en la carga del mapa
void EscenaEditor::dibujar_bloque(int x, int y) {
    QGraphicsSceneMouseEvent event;
    event.setScenePos(QPointF(x, y));
    dibujar_bloque_item(&event);
}


void EscenaEditor::actualizar_texturas(const std::string& tipo_texturas) {
    QPixmap imagen_recortada = lista_botones.obtener_imagen_item(tipo_texturas);
    QBrush brush(imagen_recortada);

    vista_escena.setBackgroundBrush(brush);

    for (const auto& item_actual: nivel_actual) {
        auto item = item_actual.second.get();
        auto mapa_asociado = item->data(KEY_MAPA_ASOCIADO).toString().toStdString();

        if (mapa_asociado.empty()) {
            continue;
        }

        auto tipo_item = item->data(KEY_TIPO_ITEM).toString().toStdString();

        auto nuevo_item = obtener_tipo_item(tipo_item) + DELIMITADOR + tipo_texturas;
        auto imagen_item = lista_botones.obtener_imagen_item(nuevo_item);
        item->setPixmap(imagen_item);
        item->setData(KEY_TIPO_ITEM, QVariant(nuevo_item.c_str()));

        if (lista_botones.obtener_tipo_item_seleccionado() == tipo_item) {
            lista_botones.actualizar_tipo_item_seleccionado(nuevo_item);
        }
    }
}


std::string EscenaEditor::obtener_tipo_item(const std::string& item_actual) {
    std::string resultado = item_actual;
    size_t pos = item_actual.rfind(DELIMITADOR);
    if (pos != std::string::npos) {
        resultado = item_actual.substr(0, pos);
    }
    return resultado;
}


std::string EscenaEditor::obtener_tipo_bloque(std::pair<int, int> coordenada) {
    auto &item = nivel_actual.at(coordenada);

    auto tipo_completo = item->data(KEY_TIPO_ITEM).toString();

    auto mapa_asociado = item->data(KEY_MAPA_ASOCIADO);
    if (not mapa_asociado.isValid()) {
        return tipo_completo.toStdString();
    }
    return obtener_tipo_item(tipo_completo.toStdString());
}


std::string EscenaEditor::obtener_tipo_escenario() {
    return lista_botones.obtener_escenario();
}


std::vector<std::pair<int, int>> EscenaEditor::obtener_items_escena() {
    std::vector<std::pair<int, int>> claves;

    for (const auto& item : nivel_actual) {
        claves.push_back(item.first);
    }
    return claves;
}


void EscenaEditor::actualizar_tipo_item_seleccionado(const std::string& nuevo_tipo_item) {
    lista_botones.actualizar_tipo_item_seleccionado(nuevo_tipo_item);
}


void EscenaEditor::limpiar_escena() {
    for (const auto& item : nivel_actual) {
        removeItem(item.second.get());
    }
    nivel_actual.clear();
    update();
}
