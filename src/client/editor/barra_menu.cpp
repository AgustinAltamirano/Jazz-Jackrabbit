#include "barra_menu.h"

#include <QFileDialog>
#include <fstream>
#include <sstream>

#include <yaml-cpp/yaml.h>

#include "constantes.h"


const std::set<std::string> BarraMenu::BLOQUES_SIN_ESCENARIO {
        "spawn_personajes",
        "spawn_enemigos",
        "gema",
        "moneda"
};


const std::unordered_map<std::string, TipoEscenario> BarraMenu::TIPO_A_ESCENARIO {
        {"castle", ESCENARIO1},
        {"carrotus", ESCENARIO2},
};


const std::unordered_map<TipoEscenario, std::string> BarraMenu::ESCENARIO_A_TIPO {
        {ESCENARIO1, "castle"},
        {ESCENARIO2, "carrotus"},
};


const std::unordered_map<std::string, TipoBloqueEscenario> BarraMenu::TIPO_A_BLOQUE {
        {"piso", PISO},
        {"bajopiso", PARED},
        {"rampa_izq", DIAGONAL},
        {"rampa_der", DIAGONAL_INVERTIDO},
        {"final_rampa_izq", SOPORTE_DIAGONAL},
        {"final_rampa_der", SOPORTE_DIAGONAL_INVERTIDO},
        {"spawn_personajes", SPAWNPOINT_JUGADOR},
        {"spawn_enemigos", SPAWNPOINT_ENEMIGO},
        {"gema", GEMA},
        {"moneda", MONEDA}
};


const std::unordered_map<TipoBloqueEscenario, std::string> BarraMenu::BLOQUE_A_TIPO {
        {PISO, "piso"},
        {PARED, "bajopiso"},
        {DIAGONAL, "rampa_izq"},
        {DIAGONAL_INVERTIDO, "rampa_der"},
        {SOPORTE_DIAGONAL, "final_rampa_izq"},
        {SOPORTE_DIAGONAL_INVERTIDO, "final_rampa_der"},
        {SPAWNPOINT_JUGADOR, "spawn_personajes"},
        {SPAWNPOINT_ENEMIGO, "spawn_enemigos"},
        {GEMA, "gema"},
        {MONEDA, "moneda"}
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
        auto tipo_escenario = TipoEscenario(std::stoi(escenario));

        for (const auto& item: yaml_mapa["items"][1]["bloques"]) {
            auto bloque = item["tipo"].as<std::string>();
            auto tipo_bloque = TipoBloqueEscenario(std::stoi(bloque));

            auto tipo_item = BLOQUE_A_TIPO.at(tipo_bloque);

            if (BLOQUES_SIN_ESCENARIO.find(tipo_item) == BLOQUES_SIN_ESCENARIO.end()) {
                tipo_item += '_' + ESCENARIO_A_TIPO.at(tipo_escenario);
            }

            int x = item["x"].as<int>(), y = item["y"].as<int>();
            escena.actualizar_tipo_item_seleccionado(tipo_item);
            escena.dibujar_bloque(x, y);
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
        auto escenario = TIPO_A_ESCENARIO.at(escena.obtener_tipo_escenario());
        yaml_mapa << YAML::Key << "escenario" << YAML::Value << escenario;
        yaml_mapa << YAML::EndMap;

        yaml_mapa << YAML::BeginMap;
        yaml_mapa << YAML::Key << "bloques";
        yaml_mapa << YAML::Value << YAML::BeginSeq;

        for (const auto& coord_item: items) {
            yaml_mapa << YAML::BeginMap;
            auto e = escena.obtener_tipo_bloque(coord_item);
            auto tipo_bloque = TIPO_A_BLOQUE.at(e);
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
