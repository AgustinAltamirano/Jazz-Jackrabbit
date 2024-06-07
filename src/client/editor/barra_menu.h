#ifndef BARRA_MENU_H
#define BARRA_MENU_H

#include <QMenuBar>
#include <set>
#include "escena_editor.h"


class BarraMenu : public QMenuBar {
public:
    explicit BarraMenu(EscenaEditor& escena);

private:
    static const std::set<TipoItemEditor> BLOQUES_SIN_ESCENARIO;

    QString ruta_mapa_actual;

    EscenaEditor& escena;

    void guardar_mapa();

    void guardar_como_mapa();

    void cargar_mapa();

    void guardar_en_yaml(const QString& ruta_archivo_guardado);
};


#endif  // BARRA_MENU_H
