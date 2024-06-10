#include "barra_menu.h"

#include <QFileDialog>
#include <fstream>
#include <sstream>

#include <yaml-cpp/yaml.h>
#include "constantes.h"


const std::set<TipoItemEditor> BarraMenu::BLOQUES_SIN_ESCENARIO {
        SPAWNPOINT_JUGADOR, SPAWNPOINT_ENEMIGO, GEMA, MONEDA
};


BarraMenu::BarraMenu(QMainWindow* parent, EscenaEditor& escena):
        QMenuBar(parent),
        escena(escena) {
    setFixedSize(ANCHO_PANTALLA, ALTO_MENU_BAR);
    addAction(TEXTO_BTN_GUARDAR, this, &BarraMenu::guardar_mapa);
    addAction(TEXTO_BTN_GUARDAR_COMO, this, &BarraMenu::guardar_como_mapa);
    addAction(TEXTO_BTN_CARGAR, this, &BarraMenu::cargar_mapa);
    addAction(TEXTO_BTN_LIMPIAR, this, &BarraMenu::limpiar_mapa);
}


void BarraMenu::guardar_como_mapa() {
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(EXTENSION_ARCHIVO_MAPA);
    dialog.setNameFilter(FILTRO_ARCHIVOS);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setWindowTitle(TITULO_DIALOG_GUARDAR);
    dialog.setDirectory(CARPETA_MAPAS);
    dialog.setGeometry(OFFSET_X_DIALOG, OFFSET_Y_DIALOG, ANCHO_DIALOG, ALTO_DIALOG);

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        auto ruta_archivo_guardado = dialog.selectedFiles().first();
        ruta_mapa_actual = ruta_archivo_guardado;
        guardar_en_yaml(ruta_archivo_guardado);
    }
}


void BarraMenu::cargar_mapa() {
    QFileDialog dialog(this);
    dialog.setNameFilter(FILTRO_ARCHIVOS);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setWindowTitle(TITULO_DIALOG_CARGAR);
    dialog.setDirectory(CARPETA_MAPAS);
    dialog.setGeometry(OFFSET_X_DIALOG, OFFSET_Y_DIALOG, ANCHO_DIALOG, ALTO_DIALOG);

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        ruta_mapa_actual = dialog.selectedFiles().first();

        std::ostringstream nuevo_titulo;

        nuevo_titulo << TITULO_VENTANA << SEPARADOR_TITULO
                     << ruta_mapa_actual.split(SEPARADOR_RUTA_FILE).last().toStdString();

        this->parentWidget()->setWindowTitle(nuevo_titulo.str().c_str());

        const std::string ruta_mapa = ruta_mapa_actual.toStdString();
        YAML::Node yaml_mapa = YAML::LoadFile(ruta_mapa);

        escena.limpiar_escena();

        auto escenario = yaml_mapa[KEY_PRINCIPAL][NODO_ESCENARIO][KEY_ESCENARIO].as<std::string>();
        auto tipo_escenario = TipoEscenarioEditor(std::stoi(escenario));
        escena.actualizar_fondo(tipo_escenario);

        for (const auto& item: yaml_mapa[KEY_PRINCIPAL][NODO_ITEMS][KEY_BLOQUES]) {
            auto bloque = item[KEY_TIPO].as<std::string>();
            auto tipo_bloque = TipoItemEditor(std::stoi(bloque));

            auto texturas = ESCENARIO_INDEFINIDO;

            if (BLOQUES_SIN_ESCENARIO.find(tipo_bloque) == BLOQUES_SIN_ESCENARIO.end()) {
                texturas = tipo_escenario;
            }

            int x = item[KEY_COORD_X].as<int>(), y = item[KEY_COORD_Y].as<int>();
            escena.dibujar_bloque(x, y, tipo_bloque, texturas);
        }
    }
}


void BarraMenu::guardar_mapa() {
    if (ruta_mapa_actual.isEmpty()) {
        guardar_como_mapa();
    } else {
        guardar_en_yaml(ruta_mapa_actual);
    }
}


void BarraMenu::guardar_en_yaml(const QString& ruta_archivo_guardado) {
    const std::string ruta_mapa = ruta_archivo_guardado.toStdString();
    YAML::Emitter yaml_mapa;
    yaml_mapa << YAML::BeginMap;
    yaml_mapa << YAML::Key << KEY_PRINCIPAL;
    yaml_mapa << YAML::Value << YAML::BeginSeq;

    auto items = escena.obtener_items_escena();

    yaml_mapa << YAML::BeginMap;
    auto escenario = escena.obtener_tipo_escenario();
    yaml_mapa << YAML::Key << KEY_ESCENARIO << YAML::Value << escenario;
    yaml_mapa << YAML::EndMap;

    if (not items.empty()) {
        yaml_mapa << YAML::BeginMap;
        yaml_mapa << YAML::Key << KEY_BLOQUES;
        yaml_mapa << YAML::Value << YAML::BeginSeq;

        for (const auto& coord_item: items) {
            yaml_mapa << YAML::BeginMap;
            auto tipo_bloque = escena.obtener_tipo_bloque(coord_item);
            yaml_mapa << YAML::Key << KEY_TIPO << YAML::Value << tipo_bloque;
            yaml_mapa << YAML::Key << KEY_COORD_X << YAML::Value << coord_item.x;
            yaml_mapa << YAML::Key << KEY_COORD_Y << YAML::Value << coord_item.y;
            yaml_mapa << YAML::EndMap;
        }
    }

    yaml_mapa << YAML::EndSeq;
    yaml_mapa << YAML::EndMap;

    std::ofstream archivo_mapa(ruta_mapa);
    archivo_mapa << yaml_mapa.c_str();
}

void BarraMenu::limpiar_mapa() {
    escena.limpiar_escena();
}
