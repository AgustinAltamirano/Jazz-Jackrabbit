#ifndef MANEJADOR_GRAFICO_H
#define MANEJADOR_GRAFICO_H


#include <QGraphicsScene>

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480
#define TAM_ITEM 32

class ManejadorGrafico {
public:
    ManejadorGrafico(QGraphicsScene& escena,
                     std::map<std::string, QPixmap>& items,
                     std::map<std::pair<int, int>, std::string>& nivel_actual);

private:
    QGraphicsScene& escena;

    std::map<std::string, QPixmap>& items;

    std::map<std::pair<int, int>, std::string>& nivel_actual;
};


#endif  // MANEJADOR_GRAFICO_H
