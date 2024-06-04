#include "ventana_inicial.h"

#include <QFontDatabase>


VentanaInicial::VentanaInicial(MenuJuego& juego):
        QMainWindow(), press_click_btn(this), reproductor_musica(), playlist(), menu_principal(juego) {
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    reproducir_musica();
    QString estilo = QString("QMainWindow {background-image: url(%1);}").arg(QString(ASSETS_PATH) + RUTA_IMG_MENU);
    setStyleSheet(estilo);
    inicializar_boton();
}


void VentanaInicial::reproducir_musica() {
    auto url = QUrl::fromLocalFile(QString(ASSETS_PATH) + RUTA_MUSICA_FONDO);
    playlist.addMedia(url);
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
    reproductor_musica.setPlaylist(&playlist);
    reproductor_musica.setVolume(VOLUMEN_MUSICA);
    reproductor_musica.play();
}


void VentanaInicial::inicializar_boton() {
    auto fuente_juego = obtener_fuente();
    press_click_btn.setGeometry(QRect(0, 0, ANCHO_PANTALLA, ALTO_PANTALLA));
    press_click_btn.setFont(fuente_juego);
    press_click_btn.setStyleSheet(
            "QPushButton {border: none; text-align: bottom; color: white; background: none;}");
    press_click_btn.setText(TEXTO_INICIO_BTN);

    connect(&press_click_btn, &QPushButton::clicked, this, &VentanaInicial::mostrar_menu_principal);
}


void VentanaInicial::mostrar_menu_principal() {
    menu_principal.move(this->pos());
    menu_principal.show();
    hide();
}


QFont obtener_fuente() {
    static auto fuente_juego = QFont();
    static bool fuente_cargada = false;

    if (!fuente_cargada) {
        int id = QFontDatabase::addApplicationFont(QString(ASSETS_PATH) + RUTA_FUENTE);

        if (id != -1) {
            QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

            if (!fontFamilies.isEmpty()) {
                fuente_cargada = true;
                const QString& fontFamily = fontFamilies.at(0);
                fuente_juego = QFont(fontFamily, TAMANIO_FUENTE);
            }
        }
    }
    return fuente_juego;
}
