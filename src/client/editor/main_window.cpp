#include "main_window.h"


MainWindow::MainWindow() :
        QMainWindow(),
        central_widget(this),
        layout_horizontal(&central_widget),
        widget_graphics_view(),
        escena(layout_vertical, &widget_graphics_view),
        widget_layout_vertical(),
        layout_vertical(&widget_layout_vertical, escena),
        menu_bar(escena)
{
    setWindowIcon(QIcon(QString(ASSETS_PATH) + RUTA_ICONO));
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
        auto nodo_item_actual = yaml_items["items"][posicion];

        auto ruta_imagen = nodo_item_actual["ruta_imagen"].as<std::string>();

        auto tipo_item = nodo_item_actual["tipo"].as<std::string>();

        std::string mapa_asociado;
        if (nodo_item_actual["mapa"].IsDefined()) {
            mapa_asociado = nodo_item_actual["mapa"].as<std::string>();
        }

        auto item_actual = ItemEscena{tipo_item,
                                      mapa_asociado,
                                      QPixmap(ruta_imagen.c_str())};

        layout_vertical.inicializar_boton_item(std::move(item_actual), posicion);
    }
}


void MainWindow::inicializar_texturas() {
    const std::string ruta_escenarios = std::string(ASSETS_PATH) + std::string(RUTA_IMG_ESCENARIOS);
    const std::string ruta_yaml_escenarios = ruta_escenarios + std::string(ESCENARIOS_CONFIG);
    YAML::Node yaml_escenarios = YAML::LoadFile(ruta_yaml_escenarios);

    for (const auto& escenario_actual: yaml_escenarios["escenarios"]) {
        auto ruta_imagen = ruta_escenarios + escenario_actual["imagen"].as<std::string>();
        auto coord_img = escenario_actual["fondo_coords"][COORD_FONDO];
        QRect rectangulo(coord_img["x"].as<int>(), coord_img["y"].as<int>(),
                         coord_img["ancho"].as<int>(), coord_img["alto"].as<int>());

        QPixmap imagen_fondo(ruta_imagen.c_str());
        auto imagen_recortada = imagen_fondo.copy(rectangulo);
        auto nombre_mapa = escenario_actual["nombre"].as<std::string>();

        auto item_actual = ItemEscena{nombre_mapa, "", imagen_recortada};

        layout_vertical.inicializar_boton_texturas(std::move(item_actual));
    }
}
