#include "boton_animado.h"

#include <QBitmap>
#include <QPainter>

#include "constantes_menu.h"


BotonAnimado::BotonAnimado(QMainWindow* parent, int num_personaje, int ancho, int alto) :
        QPushButton(parent),
        label_jugador(this),
        label_nombre(this),
        timer_frames(this),
        frame_act_jug(0),
        frame_act_nombre(0),
        cant_frames_jugador(0),
        cant_frames_nombre(0)
{
    const std::string ruta_personajes = std::string(ASSETS_PATH) + std::string(RUTA_SPRITES);
    const std::string ruta_personajes_config = ruta_personajes + std::string(PERSONAJES_CONFIG);
    YAML::Node personajes = YAML::LoadFile(ruta_personajes_config);

    auto imagen_sprites = RUTA_IMG_MENU_MULTIPLAYER2;
    QPixmap imagen(imagen_sprites);
    QRgb colorKey = qRgb(R_MULTIPLAYER, G_MULTIPLAYER, B_MULTIPLAYER);
    QBitmap mask = imagen.createMaskFromColor(colorKey, Qt::MaskInColor);
    imagen.setMask(mask);

    inicializar_texturas(personajes, num_personaje, "sprites", imagen, frames_jugador);
    cant_frames_jugador = frames_jugador.size();

    inicializar_texturas(personajes, num_personaje, "sprites_nombre", imagen, frames_nombre);
    cant_frames_nombre = frames_nombre.size();

    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    label_jugador.setGeometry(QRect(0, 0, ancho, alto));
    label_jugador.installEventFilter(this);
    label_jugador.setMouseTracking(true);

    label_nombre.setGeometry(QRect(0, SEP_NOMBRE_Y_JUG, ANCHO_SEL_NAME, ALTO_SEL_NAME));
    label_nombre.installEventFilter(this);
    label_nombre.setMouseTracking(true);
}


void BotonAnimado::inicializar_texturas(YAML::Node personajes,
                                           int num_personaje,
                                           const std::string& tipo_de_textura,
                                           QPixmap& imagen,
                                           std::vector<QPixmap>& coleccion_frames)
{
    auto personaje = personajes["personajes"][num_personaje];
    for (const auto& sprite_actual: personaje[tipo_de_textura]) {
        QRect rectangulo(sprite_actual["x"].as<int>(),
                         sprite_actual["y"].as<int>(),
                         sprite_actual["ancho"].as<int>(),
                         sprite_actual["alto"].as<int>());
        QPixmap sprite = imagen.copy(rectangulo);
        coleccion_frames.emplace_back(std::move(sprite));
    }
}


void BotonAnimado::animacion_hacia_adelante() {
    timer_frames.disconnect();
    connect(&timer_frames, &QTimer::timeout, this, &BotonAnimado::siguiente_frame);
    timer_frames.start(DURACION_FRAME);
}


void BotonAnimado::animacion_en_reversa() {
    timer_frames.disconnect();
    connect(&timer_frames, &QTimer::timeout, this, &BotonAnimado::anterior_frame);
    timer_frames.start(DURACION_FRAME);
}


void BotonAnimado::siguiente_frame() {
    frame_act_jug = std::min(frame_act_jug + 1, cant_frames_jugador - 1);
    frame_act_nombre = std::min(frame_act_nombre + 1, cant_frames_nombre - 1);
}


void BotonAnimado::anterior_frame() {
    frame_act_jug = std::max(frame_act_jug - 1, 0);
    frame_act_nombre = std::max(frame_act_nombre - 1, 0);
}


void BotonAnimado::paintEvent(QPaintEvent* event) {
    pintar_frame(frames_jugador,
                 label_jugador, frame_act_jug,
                 ANCHO_SEL_PLAYER,
                 ALTO_SEL_PLAYER);

    pintar_frame(frames_nombre,
                 label_nombre, frame_act_nombre,
                 ANCHO_SEL_NAME,
                 ALTO_SEL_NAME);
}


void BotonAnimado::pintar_frame(std::vector<QPixmap>& frames,
                                   QLabel& label,
                                   int frame_actual,
                                   int ancho, int alto)
{
    QPixmap pixmap = frames.at(frame_actual);
    label.setPixmap(pixmap.scaled(ancho, alto, Qt::KeepAspectRatio));
}


void BotonAnimado::focusInEvent(QFocusEvent* event) {
    animacion_hacia_adelante();
    clicked();
    QPushButton::focusInEvent(event); // Llama a la implementación base para mantener el comportamiento normal
}


void BotonAnimado::focusOutEvent(QFocusEvent* event) {
    animacion_en_reversa();
    QPushButton::focusOutEvent(event); // Llama a la implementación base para mantener el comportamiento normal
}


void BotonAnimado::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        clicked();
    } else {
        QPushButton::keyPressEvent(event);  // Propaga el evento al manejador por defecto
    }
}


void BotonAnimado::mouseMoveEvent(QMouseEvent *event) {
    setFocus();                 // Pone el foco en el botón cuando el mouse se mueve sobre él
    QPushButton::mouseMoveEvent(event);  // Llama al método original para que el botón funcione normalmente
}


bool BotonAnimado::eventFilter(QObject* watched, QEvent* event) {
    if (watched == &label_jugador && event->type() == QEvent::MouseMove) {
        mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    }
    // Delega el manejo del evento a la implementación base para otros casos
    return QPushButton::eventFilter(watched, event);
}
