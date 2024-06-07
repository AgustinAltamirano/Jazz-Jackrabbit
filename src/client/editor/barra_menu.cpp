#include "barra_menu.h"

#include <QFileDialog>
#include <fstream>
#include <sstream>

#include <yaml-cpp/yaml.h>
#include "constantes.h"


const std::set<TipoItemEditor> BarraMenu::BLOQUES_SIN_ESCENARIO {
        SPAWNPOINT_JUGADOR, SPAWNPOINT_ENEMIGO, GEMA, MONEDA
};


BarraMenu::BarraMenu(EscenaEditor& escena):
        QMenuBar(),
        escena(escena) {
    setFixedSize(ANCHO_PANTALLA, ALTO_MENU_BAR);
    addAction("Guardar", this, &BarraMenu::guardar_mapa);
    addAction("Guardar como", this, &BarraMenu::guardar_como_mapa);
    addAction("Cargar", this, &BarraMenu::cargar_mapa);
}


void BarraMenu::guardar_como_mapa() {
    QFileDialog dialog(this);
    dialog.setWindowTitle("Guardar mapa");
    dialog.setDefaultSuffix("yaml");
    dialog.setNameFilter("Mapas (*.yaml)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setGeometry(0, 0, 500, 500);

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        auto ruta_archivo_guardado = dialog.selectedFiles().first();
        ruta_mapa_actual = ruta_archivo_guardado;
        guardar_en_yaml(ruta_archivo_guardado);
    }
}


void BarraMenu::cargar_mapa() {
    QFileDialog dialog(this);
    dialog.setWindowTitle("Cargar mapa");
    dialog.setNameFilter("Mapas (*.yaml)");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setGeometry(0, 0, 500, 500);

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        ruta_mapa_actual = dialog.selectedFiles().first();

        std::ostringstream nuevo_titulo;

        nuevo_titulo << TITULO_VENTANA << " - "
                     << ruta_mapa_actual.split("/").last().toStdString();

        setWindowTitle(nuevo_titulo.str().c_str());

        const std::string ruta_mapa = ruta_mapa_actual.toStdString();
        YAML::Node yaml_mapa = YAML::LoadFile(ruta_mapa);

        escena.limpiar_escena();

        auto escenario = yaml_mapa["items"][0]["escenario"].as<std::string>();
        auto tipo_escenario = TipoEscenarioEditor(std::stoi(escenario));
        escena.actualizar_fondo(tipo_escenario);

        for (const auto& item: yaml_mapa["items"][1]["bloques"]) {
            auto bloque = item["tipo"].as<std::string>();
            auto tipo_bloque = TipoItemEditor(std::stoi(bloque));

            auto texturas = ESCENARIO_INDEFINIDO;

            if (BLOQUES_SIN_ESCENARIO.find(tipo_bloque) == BLOQUES_SIN_ESCENARIO.end()) {
                texturas = tipo_escenario;
            }

            int x = item["x"].as<int>(), y = item["y"].as<int>();
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
    yaml_mapa << YAML::Key << "items";
    yaml_mapa << YAML::Value << YAML::BeginSeq;

    auto items = escena.obtener_items_escena();

    if (not items.empty()) {
        yaml_mapa << YAML::BeginMap;
        auto escenario = escena.obtener_tipo_escenario();
        yaml_mapa << YAML::Key << "escenario" << YAML::Value << escenario;
        yaml_mapa << YAML::EndMap;

        yaml_mapa << YAML::BeginMap;
        yaml_mapa << YAML::Key << "bloques";
        yaml_mapa << YAML::Value << YAML::BeginSeq;

        for (const auto& coord_item: items) {
            yaml_mapa << YAML::BeginMap;
            auto tipo_bloque = escena.obtener_tipo_bloque(coord_item);
            yaml_mapa << YAML::Key << "tipo" << YAML::Value << tipo_bloque;
            yaml_mapa << YAML::Key << "x" << YAML::Value << coord_item.first;
            yaml_mapa << YAML::Key << "y" << YAML::Value << coord_item.second;
            yaml_mapa << YAML::EndMap;
        }
    }

    yaml_mapa << YAML::EndSeq;
    yaml_mapa << YAML::EndMap;

    std::ofstream archivo_mapa(ruta_mapa);
    archivo_mapa << yaml_mapa.c_str();
}
