#ifndef ESCENA_EDITOR_H
#define ESCENA_EDITOR_H


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "constantes.h"
#include "lista_botones.h"


class EscenaEditor: public QGraphicsScene {
public:
    EscenaEditor(ListaBotones& lista_botones, QWidget* widget);

    void dibujar_bloque(int x, int y, TipoItemEditor tipo, TipoEscenarioEditor texturas);

    void actualizar_texturas(TipoEscenarioEditor nuevas_texturas);

    TipoItemEditor obtener_tipo_bloque(std::pair<int, int> coordenada);

    TipoEscenarioEditor obtener_tipo_escenario();

    std::vector<std::pair<int, int>> obtener_items_escena();

    void limpiar_escena();

    void actualizar_fondo(TipoEscenarioEditor texturas);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void wheelEvent(QGraphicsSceneWheelEvent* event) override;

private:
    ListaBotones& lista_botones;

    std::map<std::pair<int, int>, std::unique_ptr<QGraphicsPixmapItem>> nivel_actual;

    QGraphicsView vista_escena;

    void dibujar_bloque_item(QGraphicsSceneMouseEvent* event);

    void borrar_bloque_item(QGraphicsSceneMouseEvent* event);

    qreal obtener_coordenada_bloque(qreal coord);
};


#endif  // ESCENA_EDITOR_H
