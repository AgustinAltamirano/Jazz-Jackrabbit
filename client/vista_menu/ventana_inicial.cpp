#include <QFontDatabase>
#include <QCoreApplication>
#include "ventana_inicial.h"
#include "menu_principal.h"


VentanaInicial::VentanaInicial():
        QMainWindow(),
        press_click_btn(this),
        fuente_juego(),
        reproductor_musica(),
        playlist(),
        menu_principal(nullptr)
{
    setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    definir_fuentes();
    reproducir_musica();
    setStyleSheet("QMainWindow {background-image: url(:/img/img/bgd_menuinicial.png);}");
    inicializar_boton();
}


void VentanaInicial::definir_fuentes()
{
    int id = QFontDatabase::addApplicationFont(":/img/img/Jazz-Jackrabbit-2.ttf");

    if (id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (!fontFamilies.isEmpty()) {
            const QString& fontFamily = fontFamilies.at(0);

            fuente_juego = QFont(fontFamily, 24);
        }
    }
}


void VentanaInicial::reproducir_musica() {
    playlist.addMedia(QUrl("qrc:/sfx/sfx/Jazz Jackrabbit 2 Music - Menu.mp3"));
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
    reproductor_musica.setPlaylist(&playlist);
    reproductor_musica.play();
}


void VentanaInicial::inicializar_boton() {
    press_click_btn.setGeometry(QRect(0, 0, ANCHO_PANTALLA, ALTO_PANTALLA));
    press_click_btn.setFont(fuente_juego);
    press_click_btn.setStyleSheet("QPushButton {border: none; text-align: bottom; color: white; background: none;}");
    press_click_btn.setText("Press click");

    connect(&press_click_btn,
            &QPushButton::clicked,
            this,
            &VentanaInicial::mostrar_menu_principal);
}


void VentanaInicial::mostrar_menu_principal()
{
    menu_principal = new MenuPrincipal(fuente_juego);
    menu_principal->show();
    hide();
}


VentanaInicial::~VentanaInicial() {
    delete menu_principal;
}