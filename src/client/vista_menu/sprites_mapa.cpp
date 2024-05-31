#include "sprites_mapa.h"

#include <algorithm>


SpritesMapa::SpritesMapa(QWidget* parent, QLabel& label_boton, int num_boton, int ancho, int alto):
        ManejadorSprites(label_boton, num_boton, ancho, alto),
        escena(parent),
        vista_escena(&escena, parent),
        mapa(),
        escala_mapa(),
        animacion_x(&escala_mapa, "xScale"),
        animacion_y(&escala_mapa, "yScale"),
        animacion_x_agrandar(&escala_mapa, "xScale"),
        animacion_y_agrandar(&escala_mapa, "yScale") {
    vista_escena.setStyleSheet("QGraphicsView { background: transparent; }");
    vista_escena.setGeometry(LEFT_M_ESCENA, TOP_M_ESCENA, ANCHO_IMG_MAPA, ALTO_IMG_MAPA);

    inicializar_mapa(num_boton);
}


void SpritesMapa::inicializar_mapa(int num_boton) {
    auto nodo_imagen_mapa = sprites["botones"][num_boton]["imagen_mapa"][0];
    QRect rectangulo(nodo_imagen_mapa["x"].as<int>(), nodo_imagen_mapa["y"].as<int>(),
                     nodo_imagen_mapa["ancho"].as<int>(), nodo_imagen_mapa["alto"].as<int>());
    QPixmap sprite = imagen_sprites.copy(rectangulo);
    mapa.setPixmap(sprite);
    escena.addItem(&mapa);

    // Esto es para que la animación se haga desde el centro de la imagen y no desde el (0, 0)
    escala_mapa.setOrigin(
            QVector3D(ORIGEN_X_ESCALA_MAPA, ORIGEN_Y_ESCALA_MAPA, ORIGEN_Z_ESCALA_MAPA));

    mapa.setTransformations({&escala_mapa});
}


void SpritesMapa::animacion_mapa(QPropertyAnimation& anim_x, QPropertyAnimation& anim_y,
                                 int escala_final) {
    anim_x.setDuration(DURACION_ANIMACION);
    anim_x.setStartValue(escala_mapa.xScale());
    anim_x.setEndValue(escala_final);

    anim_y.setDuration(DURACION_ANIMACION);
    anim_y.setStartValue(escala_mapa.yScale());
    anim_y.setEndValue(escala_final);

    anim_x.start();
    anim_y.start();
    vista_escena.show();
}


void SpritesMapa::animacion_achicar() {
    animacion_mapa(animacion_x, animacion_y, ESCALA_FINAL_ACHICAR);
}


void SpritesMapa::animacion_agrandar() {
    animacion_mapa(animacion_x_agrandar, animacion_y_agrandar, ESCALA_FINAL_AGRANDAR);
}


void SpritesMapa::siguiente_frame() {
    if (frame_act_boton == 0) {
        animacion_agrandar();
    }
    frame_act_boton = std::min(frame_act_boton + 1, cant_frames_boton - 1);
}


void SpritesMapa::anterior_frame() {
    if (frame_act_boton == cant_frames_boton - 1) {
        animacion_achicar();
    }
    frame_act_boton = std::max(frame_act_boton - 1, 0);
}


void SpritesMapa::pintar_frame_actual() { pintar_frame_boton(); }
