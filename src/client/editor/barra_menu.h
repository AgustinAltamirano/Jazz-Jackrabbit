#ifndef BARRA_MENU_H
#define BARRA_MENU_H

#include <QMenuBar>
#include <set>

#include "../vista_juego/snapshot_dto.h"

#include "escena_editor.h"


class BarraMenu : public QMenuBar {
public:
    explicit BarraMenu(EscenaEditor& escena);

private:
    static const std::set<std::string> BLOQUES_SIN_ESCENARIO;

    static const std::unordered_map<std::string, TipoEscenario> TIPO_A_ESCENARIO;

    static const std::unordered_map<TipoEscenario, std::string> ESCENARIO_A_TIPO;

    static const std::unordered_map<std::string, TipoBloqueEscenario> TIPO_A_BLOQUE;

    static const std::unordered_map<TipoBloqueEscenario, std::string> BLOQUE_A_TIPO;

    QString ruta_mapa_actual;

    void guardar_mapa();

    void guardar_como_mapa();

    void cargar_mapa();

    EscenaEditor& escena;

    void guardar_en_yaml(const QString& ruta_archivo_guardado);
};


#endif  // BARRA_MENU_H
