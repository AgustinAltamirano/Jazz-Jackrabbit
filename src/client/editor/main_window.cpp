#include "main_window.h"

#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QVariant>
#include <iostream>


MainWindow::MainWindow() :
        QMainWindow(),
        central_widget(this),
        layout_horizontal(&central_widget),
        widget_layout_vertical(),
        layout_vertical(&widget_layout_vertical),
        items(),
        escena(tipo_item_seleccionado, items),
        widget_graphics_view(),
        graphics_view(&escena, &widget_graphics_view),
        tipo_item_seleccionado(),
        menu_bar(),
        items_por_mapa()
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
        inicializar_boton_item(item_actual, posicion);
    }
}


void MainWindow::inicializar_boton_item(const YAML::Node& item_actual, int posicion) {
    QPixmap imagen_item(item_actual["ruta_imagen"].as<std::string>().c_str());

    auto boton_item = crear_boton(imagen_item, item_actual["tipo"].as<std::string>());
    boton_item->setProperty("posicion", posicion);
    items.emplace(item_actual["tipo"].as<std::string>(), imagen_item);

    connect(boton_item.get(), &QPushButton::clicked, this, &MainWindow::seleccionar_item);

    if(item_actual["mapa"].IsDefined()) {
        boton_item->hide();
        layout_vertical.addWidget(boton_item.get());
        items_por_mapa[item_actual["mapa"].as<std::string>()].emplace_back(std::move(boton_item));
    } else {
        layout_vertical.addWidget(boton_item.release());
    }
}


std::unique_ptr<QPushButton> MainWindow::crear_boton(QPixmap& imagen_item, const std::string& tipo_item) {
    auto boton_item = std::make_unique<QPushButton>();
    boton_item->setIcon(QIcon(imagen_item));
    boton_item->setIconSize(QSize(TAM_ITEM, TAM_ITEM));
    boton_item->setProperty("tipo", tipo_item.c_str());
    boton_item->setStyleSheet("QPushButton {border: none; background: none;}");
    items.emplace(tipo_item, imagen_item);
    return boton_item;
}


void MainWindow::inicializar_texturas() {
    const std::string ruta_escenarios = std::string(ASSETS_PATH) + std::string(RUTA_IMG_ESCENARIOS);
    const std::string ruta_yaml_escenarios = ruta_escenarios + std::string(ESCENARIOS_CONFIG);
    YAML::Node yaml_escenarios = YAML::LoadFile(ruta_yaml_escenarios);

    for (const auto& escenario_actual: yaml_escenarios["escenarios"]) {
        definir_boton_texturas(escenario_actual, ruta_escenarios);
    }
}


void MainWindow::definir_boton_texturas(const YAML::Node& escenario_actual,
                                        const std::string& ruta_escenarios) {

    auto ruta_imagen = ruta_escenarios + escenario_actual["imagen"].as<std::string>();
    auto coord_img = escenario_actual["fondo_coords"][COORD_FONDO];
    QRect rectangulo(coord_img["x"].as<int>(), coord_img["y"].as<int>(),
                     coord_img["ancho"].as<int>(), coord_img["alto"].as<int>());

    QPixmap imagen_fondo(ruta_imagen.c_str());
    auto imagen_recortada = imagen_fondo.copy(rectangulo);

    auto boton_escenario = crear_boton(imagen_recortada, escenario_actual["nombre"].as<std::string>());
    connect(boton_escenario.get(), &QPushButton::clicked, this, &MainWindow::seleccionar_texturas);
    layout_vertical.addWidget(boton_escenario.release());
}


void MainWindow::seleccionar_texturas() {
    auto boton_textura = qobject_cast<QPushButton*>(sender());
    auto tipo_textura_mapa = boton_textura->property("tipo").toString().toStdString();

    QPixmap imagen_recortada = items[tipo_textura_mapa];
    QBrush brush(imagen_recortada);
    graphics_view.setBackgroundBrush(brush);
    tipo_item_seleccionado = tipo_textura_mapa;

    for (const auto& mapa_actual: items_por_mapa) {
        auto tipo_mapa = mapa_actual.first;

        for (const auto& boton_actual: mapa_actual.second) {
            if (tipo_mapa != tipo_textura_mapa) {
                boton_actual->hide();
            } else {
                int posicion_en_layout = boton_actual->property("posicion").toInt();
                layout_vertical.itemAt(posicion_en_layout)->widget()->show();
            }
        }
    }
}


void MainWindow::seleccionar_item() {
    auto boton = qobject_cast<QPushButton*>(sender());
    tipo_item_seleccionado = boton->property("tipo").toString().toStdString();
}
