#ifndef MANEJADOR_SPRITES_H
#define MANEJADOR_SPRITES_H


#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constantes_menu.h"

#define RUTA_SPRITES_PJ "/menu/img/"
#define PERSONAJES_CONFIG "sprites.yaml"
#define DURACION_FRAME 50  // en ms
#define SEP_NOMBRE_Y_BTN 200


class ManejadorSprites: public QObject {
public:
    ManejadorSprites(QLabel& label_boton, int num_boton, int ancho, int alto);

    virtual void pintar_frame_actual() = 0;

    void animacion_hacia_adelante();

    void animacion_en_reversa();

private slots:
    virtual void siguiente_frame() = 0;

    virtual void anterior_frame() = 0;

protected:
    YAML::Node sprites;

    QPixmap imagen_sprites;

    void inicializar_texturas(int num_boton, const std::string& tipo_de_sprite,
                              std::vector<QPixmap>& coleccion_frames);

    int frame_act_boton;

    uint16_t cant_frames_boton;

    void pintar_frame(const std::vector<QPixmap>& frames, QLabel& label, int frame_actual,
                      int ancho, int alto);

    void pintar_frame_boton();

private:
    std::vector<QPixmap> frames_boton;

    QTimer timer_frames;

    QLabel& label_boton;

    int ancho_img;

    int alto_img;

    static YAML::Node obtener_yaml();

    static QPixmap obtener_imagen_sprites(YAML::Node& sprites, int num_boton);
};


#endif  // MANEJADOR_SPRITES_H
