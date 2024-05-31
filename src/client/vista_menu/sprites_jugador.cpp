#include "sprites_jugador.h"

#include <algorithm>


SpritesJugador::SpritesJugador(QLabel& label_boton, QLabel& label_nombre, int num_boton, int ancho,
                               int alto):
        ManejadorSprites(label_boton, num_boton, ancho, alto),
        label_nombre(label_nombre),
        frame_act_nombre(0),
        cant_frames_nombre(0) {
    inicializar_texturas(num_boton, "sprites_nombre", frames_nombre);
    cant_frames_nombre = frames_nombre.size();

    label_nombre.setGeometry(QRect(0, SEP_NOMBRE_Y_BTN, ANCHO_SEL_NAME, ALTO_SEL_NAME));
    label_nombre.setMouseTracking(true);
}


void SpritesJugador::siguiente_frame() {
    frame_act_boton = std::min(frame_act_boton + 1, cant_frames_boton - 1);
    frame_act_nombre = std::min(frame_act_nombre + 1, cant_frames_nombre - 1);
}


void SpritesJugador::anterior_frame() {
    frame_act_boton = std::max(frame_act_boton - 1, 0);
    frame_act_nombre = std::max(frame_act_nombre - 1, 0);
}


void SpritesJugador::pintar_frame_nombre() {
    pintar_frame(frames_nombre, label_nombre, frame_act_nombre, ANCHO_SEL_NAME, ALTO_SEL_NAME);
}


void SpritesJugador::pintar_frame_actual() {
    pintar_frame_boton();
    pintar_frame_nombre();
}
