#ifndef MANEJADOR_GRAFICO_H
#define MANEJADOR_GRAFICO_H


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "constantes.h"


class ManejadorGrafico : public QGraphicsScene {
public:
    ManejadorGrafico(std::string& item_seleccionado, std::map<std::string, QPixmap>& items);

    std::map<std::pair<int, int>, std::unique_ptr<QGraphicsPixmapItem>> nivel_actual;

    void dibujar_bloque(int x, int y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    std::string& tipo_item_seleccionado;

    std::map<std::string, QPixmap>& items;

    void dibujar_bloque_item(QGraphicsSceneMouseEvent* event);

    void borrar_bloque_item(QGraphicsSceneMouseEvent* event);

    qreal obtener_coordennada_bloque(qreal coord);
};


#endif  // MANEJADOR_GRAFICO_H
