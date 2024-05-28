#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H


#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QPropertyAnimation>
#include <yaml-cpp/yaml.h>


#define RUTA_SPRITES "/menu/img/"
#define PERSONAJES_CONFIG "personajes.yaml"
#define RUTA_IMG_MENU_MULTIPLAYER2 ":/img/img/Character Select.png"
#define FRAME_DURATION 70        // en ms
#define SEP_NOMBRE_Y_JUG 200


class BotonAnimado: public QPushButton {
    Q_OBJECT

public:
    BotonAnimado(int num_personaje, int ancho, int alto);

protected:
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

private slots:
    void siguiente_frame();
    void anterior_frame();

private:
    std::vector<QPixmap> frames_jugador;

    std::vector<QPixmap> frames_nombre;

    int frame_act_jug;

    int frame_act_nombre;

    QTimer timer_frames;

    QLabel label_jugador;

    QLabel label_nombre;

    int cant_frames_jugador;

    int cant_frames_nombre;

    void inicializar_texturas(YAML::Node personajes, int num_personaje,
                              const std::string& tipo_de_textura, QPixmap& imagen,
                              std::vector<QPixmap>& coleccion_frames);

    void paintEvent(QPaintEvent* event) override;

    void pintar_frame(std::vector<QPixmap>& frames,
                      QLabel& label,
                      int frame_actual,
                      int ancho, int alto);

    void animacion_hacia_adelante();

    void animacion_en_reversa();
};


#endif //SPRITEANIMATION_H
