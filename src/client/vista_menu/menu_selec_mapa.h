#ifndef MENU_SELEC_MAPA_H
#define MENU_SELEC_MAPA_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScale>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QPropertyAnimation>

#include "boton_animado.h"
#include "boton_menu.h"

#define NUM_MAPA_1 3
#define NUM_MAPA_2 4
#define NUM_MAPA_CUST 5

#define M_LEFT_LAYOUT 0
#define M_TOP_LAYOUT 0

#define ESPACIADO_ENTRE_MAPAS 100
#define M_LEFT_MAPA 100
#define M_TOP_MAPA 150
#define M_RIGHT_MAPA 0
#define M_BOTTOM_MAPA 150

#define ORIGEN_X_ESCALA_MAPA (ANCHO_IMG_MAPA / 2)
#define ORIGEN_Y_ESCALA_MAPA (ALTO_IMG_MAPA / 2)
#define ORIGEN_Z_ESCALA_MAPA 0


class MenuSeleccionMapa : public QMainWindow {
private:
    QWidget central_widget;

    QWidget vertical_layout_widget;

    QVBoxLayout vertical_layout;

    BotonAnimado opcion_mapa_1;

    BotonAnimado opcion_mapa_2;

    BotonAnimado opcion_mapa_custom;

    QGraphicsScene escena;

    QGraphicsView vista_escena;

    QGraphicsPixmapItem mapa;

    QGraphicsScale escala_mapa;

    QPropertyAnimation animacion_x;

    QPropertyAnimation animacion_y;

    QPropertyAnimation animacion_x_agrandar;

    QPropertyAnimation animacion_y_agrandar;

    void inicializar_mapa();

    void animacion_mapa(QPropertyAnimation& anim_x, QPropertyAnimation& anim_y, int escala_final);

    void animacion_achicar();

    void animacion_agrandar();

public:
    explicit MenuSeleccionMapa(QMainWindow* parent);
};


#endif  // MENU_SELEC_MAPA_H
