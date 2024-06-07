#include "escena_editor.h"

#include <QGraphicsSceneMouseEvent>
#include <QScrollBar>
#include <cmath>


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
    auto item = lista_botones.obtener_item_seleccionado();

    auto x = obtener_coordenada_bloque(event->scenePos().x());
    auto y = obtener_coordenada_bloque(event->scenePos().y());

    QRectF rect_viewport = vista_escena.mapToScene(vista_escena.viewport()->rect()).boundingRect();
    if (!rect_viewport.contains(x, y)) {
        return;
    }

    item->setPos(x, y);
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
void EscenaEditor::dibujar_bloque(int x, int y, TipoItemEditor tipo_item,
                                  TipoEscenarioEditor texturas) {
    auto item = lista_botones.obtener_item(tipo_item, texturas);
    lista_botones.actualizar_item_seleccionado(item);
    QGraphicsSceneMouseEvent event;
    event.setScenePos(QPointF(x, y));
    dibujar_bloque_item(&event);
}


void EscenaEditor::actualizar_texturas(TipoEscenarioEditor nuevas_texturas) {
    actualizar_fondo(nuevas_texturas);

    for (const auto& item_actual: nivel_actual) {
        auto item = item_actual.second.get();
        auto mapa_asociado = item->data(KEY_MAPA_ASOCIADO).value<TipoEscenarioEditor>();

        if (mapa_asociado == ESCENARIO_INDEFINIDO) {
            continue;
        }

        auto tipo_item = item->data(KEY_TIPO_ITEM).value<TipoItemEditor>();

        auto nueva_textura = lista_botones.obtener_imagen_item(tipo_item, nuevas_texturas);
        item->setPixmap(nueva_textura);
        item->setData(KEY_MAPA_ASOCIADO, QVariant(nuevas_texturas));
    }
}


TipoItemEditor EscenaEditor::obtener_tipo_bloque(std::pair<int, int> coordenada) {
    auto &item = nivel_actual.at(coordenada);
    return item->data(KEY_TIPO_ITEM).value<TipoItemEditor>();
}


TipoEscenarioEditor EscenaEditor::obtener_tipo_escenario() {
    return lista_botones.obtener_escenario();
}


std::vector<std::pair<int, int>> EscenaEditor::obtener_items_escena() {
    std::vector<std::pair<int, int>> claves;

    for (const auto& item : nivel_actual) {
        claves.push_back(item.first);
    }
    return claves;
}


void EscenaEditor::limpiar_escena() {
    for (const auto& item : nivel_actual) {
        removeItem(item.second.get());
    }
    nivel_actual.clear();
    update();
}


void EscenaEditor::actualizar_fondo(TipoEscenarioEditor texturas) {
    auto imagen_texturas = lista_botones.obtener_imagen_item(TEXTURA, texturas);
    QBrush brush(imagen_texturas);
    vista_escena.setBackgroundBrush(brush);
}
