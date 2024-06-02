#ifndef BARRA_MENU_H
#define BARRA_MENU_H


#include <QMenuBar>


class BarraMenu : public QMenuBar {
public:
    explicit BarraMenu();

private:
    QString ruta_mapa_actual;

    void guardar_mapa();

    void guardar_como_mapa();

    void cargar_mapa();
};


#endif  // BARRA_MENU_H
