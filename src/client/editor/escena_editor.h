#ifndef ESCENA_EDITOR_H
#define ESCENA_EDITOR_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "constantes.h"
#include "coordenada_punto.h"
#include "lista_botones.h"


class EscenaEditor: public QGraphicsScene {
public:
    EscenaEditor(ListaBotones& lista_botones, QWidget* widget);

    void dibujar_bloque(int x, int y, TipoItemEditor tipo, TipoEscenarioEditor texturas);

    void actualizar_texturas(TipoEscenarioEditor nuevas_texturas);

    TipoItemEditor obtener_tipo_bloque(CoordenadaPunto coordenada);

    TipoEscenarioEditor obtener_tipo_escenario();

    std::vector<CoordenadaPunto> obtener_items_escena();

    void limpiar_escena();

    void actualizar_fondo(TipoEscenarioEditor texturas);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void wheelEvent(QGraphicsSceneWheelEvent* event) override;

private:
    ListaBotones& lista_botones;

    std::map<CoordenadaPunto, std::unique_ptr<QGraphicsPixmapItem>> nivel_actual;

    QGraphicsView vista_escena;

    void dibujar_bloque_item(QGraphicsSceneMouseEvent* event);

    void borrar_bloque_item(QGraphicsSceneMouseEvent* event);

    qreal obtener_coordenada_bloque(qreal coord);
};


#endif  // ESCENA_EDITOR_H
