#include "menu_selec_mapa.h"
#include "constantes_menu.h"


MenuSeleccionMapa::MenuSeleccionMapa(QMainWindow* parent) :
        QMainWindow(parent),
        central_widget(this),
        vertical_layout_widget(&central_widget),
        vertical_layout(&vertical_layout_widget),

        opcion_mapa_1(this, NUM_MAPA_1, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),

        opcion_mapa_2(this, NUM_MAPA_2, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),

        opcion_mapa_custom(this, NUM_MAPA_CUST, ANCHO_BTN_MAPA, ALTO_BTN_MAPA),

        escena(this),
        vista_escena(&escena, &central_widget),
        mapa(),
        escala_mapa(),
        animacion_x(&escala_mapa, "xScale"),
        animacion_y(&escala_mapa, "yScale"),
        animacion_x_agrandar(&escala_mapa, "xScale"),
        animacion_y_agrandar(&escala_mapa, "yScale")
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    vertical_layout_widget.setGeometry(QRect(M_LEFT_LAYOUT,
                                             M_TOP_LAYOUT,
                                             ANCHO_PANTALLA,
                                             ALTO_PANTALLA));

    vertical_layout.setSpacing(ESPACIADO_ENTRE_MAPAS);
    vertical_layout.setContentsMargins(M_LEFT_MAPA, M_TOP_MAPA, M_RIGHT_MAPA, M_BOTTOM_MAPA);

    vertical_layout.addWidget(&opcion_mapa_1);
    vertical_layout.addWidget(&opcion_mapa_2);
    vertical_layout.addWidget(&opcion_mapa_custom);

    setCentralWidget(&central_widget);

    vista_escena.setStyleSheet("QGraphicsView { background: transparent; }");
    vista_escena.setGeometry(320, 100, ANCHO_IMG_MAPA, ALTO_IMG_MAPA);

    inicializar_mapa();
}


void MenuSeleccionMapa::inicializar_mapa() {
    QPixmap pixmap(RUTA_SPRITES_MAPA);
    QRect rectangulo(503, 4, 304, 354);
    QPixmap sprite = pixmap.copy(rectangulo);
    mapa.setPixmap(sprite);

    escena.addItem(&mapa);

    // Esto es para que la animación se haga desde el centro de la imagen y no desde el (0, 0)
    escala_mapa.setOrigin(QVector3D(ORIGEN_X_ESCALA_MAPA,
                                    ORIGEN_Y_ESCALA_MAPA,
                                    ORIGEN_Z_ESCALA_MAPA));

    mapa.setTransformations({&escala_mapa});
}


void MenuSeleccionMapa::animacion_mapa(QPropertyAnimation& anim_x, QPropertyAnimation& anim_y, int escala_final) {
    anim_x.setDuration(1500);
    anim_x.setStartValue(escala_mapa.xScale());
    anim_x.setEndValue(escala_final);

    anim_y.setDuration(1500);
    anim_y.setStartValue(escala_mapa.yScale());
    anim_y.setEndValue(escala_final);

    anim_x.start();
    anim_y.start();
    vista_escena.show();
}


void MenuSeleccionMapa::animacion_achicar() {
    animacion_mapa(animacion_x, animacion_y, 0);
}


void MenuSeleccionMapa::animacion_agrandar() {
    animacion_mapa(animacion_x_agrandar, animacion_y_agrandar, 1);
}
