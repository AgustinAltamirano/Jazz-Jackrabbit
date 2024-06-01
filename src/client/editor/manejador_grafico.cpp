#include "manejador_grafico.h"

#include <QGraphicsPixmapItem>
#include <memory>


ManejadorGrafico::ManejadorGrafico(QGraphicsScene& escena,
                                   std::map<std::string, QPixmap>& items,
                                   std::map<std::pair<int, int>, std::string>& nivel_actual) :
        escena(escena),
        items(items),
        nivel_actual(nivel_actual)
{
    for (int y = 0; y < ALTO_PANTALLA / TAM_ITEM; y++) {
        for (int x = 0; x < ANCHO_PANTALLA / TAM_ITEM; x++) {
            if (nivel_actual.find(std::make_pair(x, y)) == nivel_actual.end()) {
                continue;
            }
            auto tipo_item = nivel_actual[std::make_pair(x, y)];
            auto imagen_item = items[tipo_item];
            auto item = std::make_unique<QGraphicsPixmapItem>(imagen_item);
            item->setPos(x * TAM_ITEM, y * TAM_ITEM);
            escena.addItem(item.release());
        }
    }
}