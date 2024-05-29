#include "menu_selec_mapa.h"
#include "constantes_menu.h"
#include <QPropertyAnimation>


MenuSeleccionMapa::MenuSeleccionMapa(QMainWindow* parent) :
        QMainWindow(parent),
        central_widget(this),
        vertical_layout_widget(&central_widget),
        vertical_layout(&vertical_layout_widget),

        opcion_mapa_1(this,
                      NUM_MAPA_1,
                      ANCHO_IMG_MAPA,
                      ALTO_IMG_MAPA),

        opcion_mapa_2(this,
                      NUM_MAPA_2,
                      ANCHO_IMG_MAPA,
                      ALTO_IMG_MAPA),

        opcion_mapa_custom(this,
                           NUM_MAPA_CUST,
                           ANCHO_IMG_MAPA,
                           ALTO_IMG_MAPA)
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    vertical_layout_widget.setGeometry(QRect(M_LEFT_LAYOUT,
                                             M_TOP_LAYOUT,
                                             ANCHO_PANTALLA,
                                             ALTO_PANTALLA));

    vertical_layout.setSpacing(ESPACIADO_ENTRE_MAPAS);
    vertical_layout.setContentsMargins(M_LEFT_MAPA, M_TOP_MAPA, M_RIGHT_MAPA, M_BOTTOM_MAPA);

//    conectar_botones();

    vertical_layout.addWidget(&opcion_mapa_1);
    vertical_layout.addWidget(&opcion_mapa_2);
    vertical_layout.addWidget(&opcion_mapa_custom);

    setCentralWidget(&central_widget);
}


//void MenuSeleccionMapa::focusInEvent(QFocusEvent* event) {
//    int offset_x = 0;
//    int offset_y = 0;
////    animation->setStartValue(QRect(offset_x, offset_y, 0, 0));
////    animation->setEndValue(QRect(offset_x, offset_y, ANCHO_IMG_MAP, ALTO_IMG_MAP));
////    animation->start();
//}
//
//
//void MenuSeleccionMapa::focusOutEvent(QFocusEvent* event) {
//    int offset_x = 0;
//    int offset_y = 0;
//    animation->setStartValue(QRect(offset_x, offset_y, ANCHO_IMG_MAP, ALTO_IMG_MAP));
//    animation->setEndValue(QRect(offset_x, offset_y, 0, 0));
//    animation->start();
//}
