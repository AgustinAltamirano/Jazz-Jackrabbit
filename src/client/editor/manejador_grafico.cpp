#include "manejador_grafico.h"

#include <QGraphicsSceneMouseEvent>
#include <cmath>


ManejadorGrafico::ManejadorGrafico(std::string& item_seleccionado, std::map<std::string, QPixmap>& items) :
        QGraphicsScene(QRectF(0, 0, ANCHO_PANTALLA, ALTO_PANTALLA)),
        tipo_item_seleccionado(item_seleccionado),
        items(items),
        nivel_actual() {}


void ManejadorGrafico::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    mouseMoveEvent(event);
    QGraphicsScene::mousePressEvent(event);
}


void ManejadorGrafico::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        dibujar_bloque_item(event);
    } else if (event->buttons() & Qt::RightButton) {
        borrar_bloque_item(event);
    }
    QGraphicsScene::mouseMoveEvent(event);
}


void ManejadorGrafico::dibujar_bloque_item(QGraphicsSceneMouseEvent* event) {
    auto imagen_item = items[tipo_item_seleccionado];
    auto item = std::make_unique<QGraphicsPixmapItem>(imagen_item);

    auto x = obtener_coordennada_bloque(event->scenePos().x());
    auto y = obtener_coordennada_bloque(event->scenePos().y());

    item->setPos(x, y);
    item->setData(0, QVariant(tipo_item_seleccionado.c_str()));

    addItem(item.get());
    nivel_actual[std::make_pair(x, y)] = std::move(item);
}


void ManejadorGrafico::borrar_bloque_item(QGraphicsSceneMouseEvent* event) {
    auto x = obtener_coordennada_bloque(event->scenePos().x());
    auto y = obtener_coordennada_bloque(event->scenePos().y());

    auto item = nivel_actual.find(std::make_pair(x, y));
    if (item != nivel_actual.end()) {
        removeItem(item->second.get());
        nivel_actual.erase(item);
    }
}


qreal ManejadorGrafico::obtener_coordennada_bloque(qreal coord) {
    return static_cast<int>(std::floor(coord) / TAM_ITEM) * TAM_ITEM;
}


void ManejadorGrafico::dibujar_bloque(int x, int y) {
    QGraphicsSceneMouseEvent event;
    event.setScenePos(QPointF(x, y));
    dibujar_bloque_item(&event);
}
