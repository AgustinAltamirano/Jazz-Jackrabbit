#ifndef ESCENA_EDITOR_H
#define ESCENA_EDITOR_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "constantes.h"
#include "lista_botones.h"


class EscenaEditor: public QGraphicsScene {
public:
    explicit EscenaEditor(ListaBotones& lista_botones, QGraphicsView& vista_escena);

    void dibujar_bloque(int x, int y);

    void actualizar_texturas(const std::string& tipo_texturas);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void wheelEvent(QGraphicsSceneWheelEvent* event) override;

private:
    ListaBotones& lista_botones;

    std::map<std::pair<int, int>, std::unique_ptr<QGraphicsPixmapItem>> nivel_actual;

    QGraphicsView& vista_escena;

    void dibujar_bloque_item(QGraphicsSceneMouseEvent* event);

    void borrar_bloque_item(QGraphicsSceneMouseEvent* event);

    qreal obtener_coordenada_bloque(qreal coord);

    std::string obtener_tipo_item(const std::string& item_actual, const std::string& nuevas_texturas);
};


#endif  // ESCENA_EDITOR_H
