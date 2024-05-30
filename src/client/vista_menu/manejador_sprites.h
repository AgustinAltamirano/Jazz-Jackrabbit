#ifndef MANEJADOR_TEXTURAS_H
#define MANEJADOR_TEXTURAS_H


#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constantes_menu.h"

#define RUTA_SPRITES "/menu/img/"
#define PERSONAJES_CONFIG "sprites.yaml"
#define RUTA_IMG ":/img/img/"
#define DURACION_FRAME 50  // en ms
#define SEP_NOMBRE_Y_BTN 200


class ManejadorSprites: public QObject {
public:
    ManejadorSprites(QLabel& label_boton, QLabel& label_nombre, int num_boton, int ancho, int alto);

    void pintar_frame_boton();

    void pintar_frame_nombre();

    void animacion_hacia_adelante();

    void animacion_en_reversa();

private slots:
    void siguiente_frame();

    void anterior_frame();

private:
    std::vector<QPixmap> frames_boton;

    std::vector<QPixmap> frames_nombre;

    int frame_act_boton;

    int frame_act_nombre;

    QTimer timer_frames;

    QLabel& label_boton;

    QLabel& label_nombre;

    int ancho_img;

    int alto_img;

    uint16_t cant_frames_boton;

    uint16_t cant_frames_nombre;

    void inicializar_texturas(YAML::Node sprites, int num_boton, const std::string& tipo_de_sprite,
                              QPixmap& imagen, std::vector<QPixmap>& coleccion_frames);

    void pintar_frame(const std::vector<QPixmap>& frames, QLabel& label, int frame_actual,
                      int ancho, int alto);
};


#endif  // MANEJADOR_TEXTURAS_H
