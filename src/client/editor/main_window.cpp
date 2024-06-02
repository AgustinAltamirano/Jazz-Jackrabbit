#include "main_window.h"


MainWindow::MainWindow() :
        QMainWindow(),
        central_widget(this),
        layout_horizontal(&central_widget),
        widget_graphics_view(),
        escena(layout_vertical),
        graphics_view(&escena, &widget_graphics_view),
        widget_layout_vertical(),
        layout_vertical(&widget_layout_vertical, graphics_view),
        menu_bar()
{
    inicializar_items();
    inicializar_texturas();
    setMenuBar(&menu_bar);
    setFixedSize(ANCHO_PANTALLA + MARGEN_ANCHO, ALTO_PANTALLA + MARGEN_ALTO);
    layout_horizontal.addWidget(&widget_layout_vertical);
    widget_layout_vertical.setFixedSize(ALTO_LISTA_ITEMS, ALTO_PANTALLA);
    layout_horizontal.addWidget(&widget_graphics_view);
    widget_graphics_view.setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    setCentralWidget(&central_widget);
    setWindowTitle(TITULO_VENTANA);
}


void MainWindow::inicializar_items() {
    const std::string ruta_items = std::string(ASSETS_PATH) + std::string(RUTA_IMG_ITEMS);
    const std::string ruta_yaml = ruta_items + std::string(ITEMS_CONFIG);
    YAML::Node yaml_items = YAML::LoadFile(ruta_yaml);

    for (int posicion = 0; posicion < yaml_items["items"].size(); posicion++) {
        auto item_actual = yaml_items["items"][posicion];

        QPixmap imagen_item(item_actual["ruta_imagen"].as<std::string>().c_str());
        auto tipo_item = item_actual["tipo"].as<std::string>();

        std::string mapa_asociado;
        if (item_actual["mapa"].IsDefined()) {
            mapa_asociado = item_actual["mapa"].as<std::string>();
        }

        layout_vertical.inicializar_boton_item(imagen_item, tipo_item, mapa_asociado, posicion);
    }
}


void MainWindow::inicializar_texturas() {
    const std::string ruta_escenarios = std::string(ASSETS_PATH) + std::string(RUTA_IMG_ESCENARIOS);
    const std::string ruta_yaml_escenarios = ruta_escenarios + std::string(ESCENARIOS_CONFIG);
    YAML::Node yaml_escenarios = YAML::LoadFile(ruta_yaml_escenarios);

    for (const auto& escenario_actual: yaml_escenarios["escenarios"]) {
        layout_vertical.inicializar_boton_texturas(escenario_actual, ruta_escenarios);
    }
}
