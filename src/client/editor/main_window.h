#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QGraphicsView>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include <yaml-cpp/yaml.h>

#include "barra_menu.h"
#include "manejador_grafico.h"


class MainWindow : public QMainWindow {
public:
    explicit MainWindow();

private Q_SLOTS:
    void seleccionar_item();

    void seleccionar_texturas();

private:
    QWidget central_widget;

    QHBoxLayout layout_horizontal;

    QWidget widget_layout_vertical;

    QVBoxLayout layout_vertical;

    std::map<std::string, QPixmap> items;

    ManejadorGrafico escena;

    QWidget widget_graphics_view;

    QGraphicsView graphics_view;

    std::string tipo_item_seleccionado;

    BarraMenu menu_bar;

    std::map<std::string, std::vector<std::unique_ptr<QPushButton>>> items_por_mapa;

    void inicializar_items();

    void inicializar_texturas();

    void inicializar_boton_item(const YAML::Node& item_actual, int posicion);

    std::unique_ptr<QPushButton> crear_boton(QPixmap& imagen_item, const std::string& tipo_item);

    void definir_boton_texturas(const YAML::Node& item_actual, const std::string& ruta_escenarios);
};


#endif  // MAIN_WINDOW_H
