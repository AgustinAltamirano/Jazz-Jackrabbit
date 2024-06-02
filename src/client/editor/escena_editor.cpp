#include "escena_editor.h"

#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <sstream>


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

    auto x = obtener_coordenada_bloque(event->scenePos().x());
    auto y = obtener_coordenada_bloque(event->scenePos().y());

    item->setPos(x, y);

    auto tipo_item = lista_botones.obtener_tipo_item_seleccionado();
    item->setData(KEY_TIPO_ITEM, QVariant(tipo_item.c_str()));
    item->setData(KEY_MAPA_ASOCIADO, lista_botones.obtener_mapa_item(tipo_item).c_str());

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
    for (const auto& item_actual: nivel_actual) {
        auto item = item_actual.second.get();
        auto mapa_asociado = item->data(KEY_MAPA_ASOCIADO).toString().toStdString();

        if (mapa_asociado.empty()) {
            continue;
        }

        auto tipo_item = item->data(KEY_TIPO_ITEM).toString().toStdString();

        auto nuevo_item = obtener_tipo_item(tipo_item, tipo_texturas);
        auto imagen_item = lista_botones.obtener_imagen_item(nuevo_item);
        item->setPixmap(imagen_item);
        item->setData(KEY_TIPO_ITEM, QVariant(nuevo_item.c_str()));
    }
}


std::string EscenaEditor::obtener_tipo_item(const std::string& item_actual, const std::string& nuevas_texturas) {
    std::vector<std::string> tipo_item_abs;
    std::string stream;
    std::istringstream tokenStream(item_actual);
    std::string delimitador = DELIMITADOR;

    while (std::getline(tokenStream, stream, delimitador.c_str()[0]))
        tipo_item_abs.push_back(stream);

    tipo_item_abs.at(tipo_item_abs.size()-1) = nuevas_texturas;

    std::string resultado = std::accumulate(std::begin(tipo_item_abs), std::end(tipo_item_abs), std::string(),
                                            [delimitador](const std::string& a, const std::string& b) -> std::string {
                                                return a + (!a.empty() ? delimitador : "") + b;
                                            });
    return resultado;
}
