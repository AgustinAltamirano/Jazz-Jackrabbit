#include "main_window.h"

#include <QPushButton>

#include <yaml-cpp/yaml.h>

#include "manejador_grafico.h"


MainWindow::MainWindow() :
        QMainWindow(),
        central_widget(this),
        layout_horizontal(&central_widget),
        widget_layout_vertical(),
        layout_vertical(&widget_layout_vertical),
        escena(),
        widget_graphics_view(),
        graphics_view(&escena, &widget_graphics_view),
        items(),
        nivel_actual()
{
    const std::string ruta_sprites = std::string(ASSETS_PATH) + std::string("/editor/img/");
    const std::string ruta_yaml = ruta_sprites + std::string("items.yaml");
    YAML::Node yaml_items = YAML::LoadFile(ruta_yaml);

    for (const auto& item_actual: yaml_items["items"]) {
        QPixmap imagen_item(item_actual["ruta_imagen"].as<std::string>().c_str());
        auto boton_item = std::make_unique<QPushButton>();
        boton_item->setIcon(QIcon(imagen_item));
        boton_item->setIconSize(QSize(34, 34));
        boton_item->setStyleSheet("QPushButton {border: none; background: none;}");
        layout_vertical.addWidget(boton_item.release());
        items.emplace(item_actual["tipo"].as<std::string>(), imagen_item);
    }
    setFixedSize(700, 500);
    layout_horizontal.addWidget(&widget_layout_vertical);
    widget_layout_vertical.setFixedSize(50, 480);
    layout_horizontal.addWidget(&widget_graphics_view);
    graphics_view.setFixedSize(640, 480);
    setCentralWidget(&central_widget);
    setWindowTitle("Editor de mapas");

    auto* manejador_escena = new ManejadorGrafico(escena, items, nivel_actual);
}
