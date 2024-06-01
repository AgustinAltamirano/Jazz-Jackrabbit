#ifndef MANEJADOR_SPRITES_JUG_H
#define MANEJADOR_SPRITES_JUG_H


#include <vector>

#include "manejador_sprites.h"


class SpritesJugador: public ManejadorSprites {
public:
    SpritesJugador(QLabel& label_boton, QLabel& label_nombre, int num_boton, int ancho, int alto);

    void pintar_frame_actual() override;

private slots:
    void siguiente_frame() override;

    void anterior_frame() override;

private:
    std::vector<QPixmap> frames_nombre;

    int frame_act_nombre;

    QLabel& label_nombre;

    uint16_t cant_frames_nombre;

    void pintar_frame_nombre();
};


#endif  // MANEJADOR_SPRITES_JUG_H
