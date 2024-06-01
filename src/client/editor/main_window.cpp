#include "main_window.h"

#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QVariant>


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
        menu_bar()
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
        definir_boton_item(item_actual);
    }

    setMenuBar(&menu_bar);
    menu_bar.setFixedSize(ANCHO_PANTALLA, ALTO_MENU_BAR);
    menu_bar.addAction("Guardar", this, &MainWindow::guardar_mapa);
    menu_bar.addAction("Guardar como", this, &MainWindow::guardar_como_mapa);
    menu_bar.addAction("Cargar", this, &MainWindow::cargar_mapa);

    setFixedSize(ANCHO_PANTALLA + MARGEN_ANCHO, ALTO_PANTALLA + MARGEN_ALTO);
    layout_horizontal.addWidget(&widget_layout_vertical);
    widget_layout_vertical.setFixedSize(ALTO_LISTA_ITEMS, ALTO_PANTALLA);
    layout_horizontal.addWidget(&widget_graphics_view);
    widget_graphics_view.setFixedSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    setCentralWidget(&central_widget);
    setWindowTitle(TITULO_VENTANA);
}


void MainWindow::definir_boton_item(const YAML::Node& item_actual) {
    QPixmap imagen_item(item_actual["ruta_imagen"].as<std::string>().c_str());

    auto boton_item = std::make_unique<QPushButton>();
    boton_item->setIcon(QIcon(imagen_item));
    boton_item->setIconSize(QSize(TAM_ITEM, TAM_ITEM));
    boton_item->setProperty("tipo", item_actual["tipo"].as<std::string>().c_str());
    boton_item->setStyleSheet("QPushButton {border: none; background: none;}");

    connect(boton_item.get(), &QPushButton::clicked, this, &MainWindow::definir_item);

    layout_vertical.addWidget(boton_item.release());
    items.emplace(item_actual["tipo"].as<std::string>(), imagen_item);
}


void MainWindow::definir_item() {
    auto boton = qobject_cast<QPushButton*>(sender());
    tipo_item_seleccionado = boton->property("tipo").toString().toStdString();
}


void MainWindow::guardar_como_mapa() {
    QFileDialog dialog(this);
    dialog.setWindowTitle("Guardar mapa");
    dialog.setDefaultSuffix("yaml");
    dialog.setNameFilter("Mapas (*.yaml)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setGeometry(0, 0, 500, 500);

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        auto ruta_archivo_guardado = dialog.selectedFiles().first();
    }
}


void MainWindow::cargar_mapa() {
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
    }
}


void MainWindow::guardar_mapa() {
    if (ruta_mapa_actual.isEmpty()) {
        guardar_como_mapa();
    }
    setFixedSize(560, 510);
    layout_horizontal.addWidget(&widget_layout_vertical);
    widget_layout_vertical.setFixedSize(50, 500);
    layout_horizontal.addWidget(&widget_graphics_view);
    graphics_view.setFixedSize(500, 500);
    setCentralWidget(&central_widget);
}
