#ifndef MANEJADOR_TEXTURAS_H
#define MANEJADOR_TEXTURAS_H


#include <QLabel>
#include <QPushButton>
#include <QTimer>

#include <yaml-cpp/yaml.h>
#include "constantes_menu.h"

#define RUTA_SPRITES "/menu/img/"
#define PERSONAJES_CONFIG "personajes.yaml"
#define RUTA_IMG_MENU_MULTIPLAYER2 ":/img/img/Character Select.png"
#define DURACION_FRAME 50        // en ms
#define SEP_NOMBRE_Y_JUG 200


class ManejadorSprites: public QObject {
public:
    ManejadorSprites(QLabel& label_jugador, QLabel& label_nombre, int personaje, int ancho, int alto);

    void pintar_frame_jugador();

    void pintar_frame_nombre();

    void animacion_hacia_adelante();

    void animacion_en_reversa();

private slots:
    void siguiente_frame();

    void anterior_frame();

private:
    std::vector<QPixmap> frames_jugador;

    std::vector<QPixmap> frames_nombre;

    int frame_act_jug;

    int frame_act_nombre;

    QTimer timer_frames;

    QLabel& label_jugador;

    QLabel& label_nombre;

    uint16_t cant_frames_jugador;

    uint16_t cant_frames_nombre;

    void inicializar_texturas(YAML::Node personajes, int num_personaje,
                              const std::string& tipo_de_textura, QPixmap& imagen,
                              std::vector<QPixmap>& coleccion_frames);

    void pintar_frame(std::vector<QPixmap>& frames,
                      QLabel& label,
                      int frame_actual,
                      int ancho, int alto);
};


#endif  // MANEJADOR_TEXTURAS_H
