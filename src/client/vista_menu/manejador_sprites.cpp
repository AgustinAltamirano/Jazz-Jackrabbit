#include "manejador_sprites.h"

#include <QBitmap>
#include <QtWidgets>
#include <utility>


ManejadorSprites::ManejadorSprites(QLabel& label_boton, int num_boton, int ancho, int alto):
        QObject(),
        sprites(obtener_yaml()),
        imagen_sprites(obtener_imagen_sprites(sprites, num_boton)),
        label_boton(label_boton),
        timer_frames(this),
        ancho_img(ancho),
        alto_img(alto),
        frame_act_boton(0),
        cant_frames_boton(0) {
    inicializar_texturas(num_boton, "sprites", frames_boton);
    cant_frames_boton = frames_boton.size();

    label_boton.setGeometry(QRect(0, 0, ancho, alto));
    label_boton.setMouseTracking(true);
}


void ManejadorSprites::inicializar_texturas(int num_boton, const std::string& tipo_de_sprite,
                                            std::vector<QPixmap>& coleccion_frames) {
    auto boton = sprites["botones"][num_boton];
    for (const auto& sprite_actual: boton[tipo_de_sprite]) {
        QRect rectangulo(sprite_actual["x"].as<int>(), sprite_actual["y"].as<int>(),
                         sprite_actual["ancho"].as<int>(), sprite_actual["alto"].as<int>());
        QPixmap sprite = imagen_sprites.copy(rectangulo);
        coleccion_frames.emplace_back(std::move(sprite));
    }
}


YAML::Node ManejadorSprites::obtener_yaml() {
    const std::string ruta_sprites = std::string(ASSETS_PATH) + std::string(RUTA_SPRITES);
    const std::string ruta_yaml = ruta_sprites + std::string(PERSONAJES_CONFIG);
    YAML::Node yaml_sprites = YAML::LoadFile(ruta_yaml);
    return yaml_sprites;
}


QPixmap ManejadorSprites::obtener_imagen_sprites(YAML::Node& sprites, int num_boton) {
    auto imagen_sprites = RUTA_IMG + sprites["botones"][num_boton]["imagen"].as<std::string>();
    QPixmap imagen(imagen_sprites.c_str());
    QRgb colorKey = qRgb(R_MULTIPLAYER, G_MULTIPLAYER, B_MULTIPLAYER);
    QBitmap mask = imagen.createMaskFromColor(colorKey, Qt::MaskInColor);
    imagen.setMask(mask);
    return imagen;
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


void ManejadorSprites::pintar_frame_boton() {
    pintar_frame(frames_boton, label_boton, frame_act_boton, ancho_img, alto_img);
}


void ManejadorSprites::pintar_frame(const std::vector<QPixmap>& frames, QLabel& label,
                                    int frame_actual, int ancho, int alto) {
    if (not frames.empty()) {
        const QPixmap& pixmap = frames.at(frame_actual);
        label.setPixmap(pixmap.scaled(ancho, alto, Qt::KeepAspectRatio));
    }
}
