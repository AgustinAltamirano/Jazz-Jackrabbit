#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QGraphicsView>
#include <QMainWindow>
#include <QVBoxLayout>
#include <yaml-cpp/yaml.h>

#include "manejador_grafico.h"


class MainWindow : public QMainWindow {
public:
    explicit MainWindow();

private Q_SLOTS:
    void definir_item();

private:
    QWidget central_widget;

    QHBoxLayout layout_horizontal;

    QWidget widget_layout_vertical;

    QVBoxLayout layout_vertical;

    std::map<std::string, QPixmap> items;

    ManejadorGrafico escena;

    QWidget widget_graphics_view;

    QGraphicsView graphics_view;

    void definir_boton_item(const YAML::Node& item_actual);

    std::string tipo_item_seleccionado;
};


#endif  // MAIN_WINDOW_H
