#ifndef MANEJADOR_SPRITES_MAPA_H
#define MANEJADOR_SPRITES_MAPA_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScale>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <vector>

#include "manejador_sprites.h"


#define ORIGEN_X_ESCALA_MAPA (ANCHO_IMG_MAPA / 2)
#define ORIGEN_Y_ESCALA_MAPA (ALTO_IMG_MAPA / 2)
#define ORIGEN_Z_ESCALA_MAPA 0

#define LEFT_M_ESCENA 320
#define TOP_M_ESCENA 100

#define DURACION_ANIMACION 600  // ms

#define ESCALA_FINAL_ACHICAR 0
#define ESCALA_FINAL_AGRANDAR 1


class SpritesMapa: public ManejadorSprites {
public:
    SpritesMapa(QWidget* parent, QLabel& label_boton, int num_boton, int ancho, int alto);

    void pintar_frame_actual() override;

private slots:
    void siguiente_frame() override;

    void anterior_frame() override;

private:
    QGraphicsScene escena;

    QGraphicsView vista_escena;

    QGraphicsPixmapItem mapa;

    QGraphicsScale escala_mapa;

    QPropertyAnimation animacion_x;

    QPropertyAnimation animacion_y;

    QPropertyAnimation animacion_x_agrandar;

    QPropertyAnimation animacion_y_agrandar;

    void inicializar_mapa(int num_boton);

    void animacion_mapa(QPropertyAnimation& anim_x, QPropertyAnimation& anim_y, int escala_final);

    void animacion_achicar();

    void animacion_agrandar();
};


#endif  // MANEJADOR_SPRITES_MAPA_H
