#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QGraphicsView>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include <yaml-cpp/yaml.h>

#include "barra_menu.h"
#include "escena_editor.h"
#include "lista_botones.h"


class MainWindow : public QMainWindow {
public:
    explicit MainWindow();

private:
    QWidget central_widget;

    QHBoxLayout layout_horizontal;

    QWidget widget_layout_vertical;

    ListaBotones layout_vertical;

    EscenaEditor escena;

    QWidget widget_graphics_view;

    QGraphicsView graphics_view;

    BarraMenu menu_bar;

    void inicializar_items();

    void inicializar_texturas();
};


#endif  // MAIN_WINDOW_H
