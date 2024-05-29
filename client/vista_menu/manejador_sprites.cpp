#include <QBitmap>
#include <QtWidgets>

#include "manejador_sprites.h"


ManejadorSprites::ManejadorSprites(QLabel& label_boton, QLabel& label_nombre, int num_boton,
                                     int ancho, int alto):
        QObject(),
        label_boton(label_boton),
        label_nombre(label_nombre),
        timer_frames(this),
        ancho_img(ancho),
        alto_img(alto),
        frame_act_boton(0),
        frame_act_nombre(0),
        cant_frames_boton(0),
        cant_frames_nombre(0)
{
    const std::string ruta_personajes = std::string(ASSETS_PATH) + std::string(RUTA_SPRITES);
    const std::string ruta_personajes_config = ruta_personajes + std::string(PERSONAJES_CONFIG);
    YAML::Node botones = YAML::LoadFile(ruta_personajes_config);

    auto imagen_sprites = RUTA_IMG + botones["botones"][num_boton]["imagen"].as<std::string>();
    QPixmap imagen(imagen_sprites.c_str());
    QRgb colorKey = qRgb(R_MULTIPLAYER, G_MULTIPLAYER, B_MULTIPLAYER);
    QBitmap mask = imagen.createMaskFromColor(colorKey, Qt::MaskInColor);
    imagen.setMask(mask);

    inicializar_texturas(botones, num_boton, "sprites", imagen, frames_boton);
    cant_frames_boton = frames_boton.size();

    inicializar_texturas(botones, num_boton, "sprites_nombre", imagen, frames_nombre);
    cant_frames_nombre = frames_nombre.size();

    label_boton.setGeometry(QRect(0, 0, ancho, alto));
    label_boton.setMouseTracking(true);

    label_nombre.setGeometry(QRect(0, SEP_NOMBRE_Y_BTN, ANCHO_SEL_NAME, ALTO_SEL_NAME));
    label_nombre.setMouseTracking(true);
}


void ManejadorSprites::inicializar_texturas(YAML::Node sprites,
                                            int num_boton,
                                            const std::string& tipo_de_sprite,
                                            QPixmap& imagen,
                                            std::vector<QPixmap>& coleccion_frames)
{
    auto boton = sprites["botones"][num_boton];
    for (const auto& sprite_actual: boton[tipo_de_sprite]) {
        QRect rectangulo(sprite_actual["x"].as<int>(),
                         sprite_actual["y"].as<int>(),
                         sprite_actual["ancho"].as<int>(),
                         sprite_actual["alto"].as<int>());
        QPixmap sprite = imagen.copy(rectangulo);
        coleccion_frames.emplace_back(std::move(sprite));
    }
}


void ManejadorSprites::animacion_hacia_adelante() {
    timer_frames.disconnect();
    QObject::connect(&timer_frames, &QTimer::timeout, this, &ManejadorSprites::siguiente_frame);
    timer_frames.start(DURACION_FRAME);
}


void ManejadorSprites::animacion_en_reversa() {
    timer_frames.disconnect();
    QObject::connect(&timer_frames, &QTimer::timeout, this, &ManejadorSprites::anterior_frame);
    timer_frames.start(DURACION_FRAME);
}


void ManejadorSprites::siguiente_frame() {
    frame_act_boton = std::min(frame_act_boton + 1, cant_frames_boton - 1);
    frame_act_nombre = std::min(frame_act_nombre + 1, cant_frames_nombre - 1);
}


void ManejadorSprites::anterior_frame() {
    frame_act_boton = std::max(frame_act_boton - 1, 0);
    frame_act_nombre = std::max(frame_act_nombre - 1, 0);
}


void ManejadorSprites::pintar_frame_boton() {
    pintar_frame(frames_boton, label_boton, frame_act_boton, ancho_img, alto_img);
}


void ManejadorSprites::pintar_frame_nombre() {
    pintar_frame(frames_nombre,
                 label_nombre,
                 frame_act_nombre,
                 ANCHO_SEL_NAME,
                 ALTO_SEL_NAME);
}


void ManejadorSprites::pintar_frame(std::vector<QPixmap>& frames,
                                    QLabel& label,
                                    int frame_actual,
                                    int ancho, int alto)
{
    if (not frames.empty()) {
        QPixmap pixmap = frames.at(frame_actual);
        label.setPixmap(pixmap.scaled(ancho, alto, Qt::KeepAspectRatio));
    }
}