#include "escena_editor.h"

#include <QGraphicsSceneMouseEvent>
#include <cmath>


EscenaEditor::EscenaEditor(ListaBotones& lista_botones) :
        QGraphicsScene(QRectF(0, 0, ANCHO_PANTALLA, ALTO_PANTALLA)),
        lista_botones(lista_botones),
        nivel_actual() {}


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


void EscenaEditor::dibujar_bloque_item(QGraphicsSceneMouseEvent* event) {
    auto imagen_item = lista_botones.obtener_imagen_item_seleccionado();
    auto item = std::make_unique<QGraphicsPixmapItem>(imagen_item);

    auto x = obtener_coordennada_bloque(event->scenePos().x());
    auto y = obtener_coordennada_bloque(event->scenePos().y());

    item->setPos(x, y);

    auto tipo_mapa = lista_botones.obtener_tipo_item_seleccionado();
    item->setData(0, QVariant(tipo_mapa.c_str()));

//    if (tipo_mapa == "castle" || tipo_mapa == "carrotus") {
//        return;
//    }

    addItem(item.get());
    nivel_actual[std::make_pair(x, y)] = std::move(item);
}


void EscenaEditor::borrar_bloque_item(QGraphicsSceneMouseEvent* event) {
    auto x = obtener_coordennada_bloque(event->scenePos().x());
    auto y = obtener_coordennada_bloque(event->scenePos().y());

    auto item = nivel_actual.find(std::make_pair(x, y));
    if (item != nivel_actual.end()) {
        removeItem(item->second.get());
        nivel_actual.erase(item);
    }
}


qreal EscenaEditor::obtener_coordennada_bloque(qreal coord) {
    return static_cast<int>(std::floor(coord) / TAM_ITEM) * TAM_ITEM;
}


// Es para usar desde fuera de la clase en la carga del mapa
void EscenaEditor::dibujar_bloque(int x, int y) {
    QGraphicsSceneMouseEvent event;
    event.setScenePos(QPointF(x, y));
    dibujar_bloque_item(&event);
}
