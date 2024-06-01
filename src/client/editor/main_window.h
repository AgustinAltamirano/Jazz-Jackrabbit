#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QVBoxLayout>


class MainWindow : public QMainWindow {
public:
    explicit MainWindow();

private:
    QWidget central_widget;

    QHBoxLayout layout_horizontal;

    QWidget widget_layout_vertical;

    QVBoxLayout layout_vertical;

    QWidget widget_graphics_view;

    QGraphicsScene escena;

    QGraphicsView graphics_view;

    std::map<std::string, QPixmap> items;

    std::map<std::pair<int, int>, std::string> nivel_actual;
};


#endif  // MAIN_WINDOW_H
