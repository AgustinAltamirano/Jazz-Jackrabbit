#include <QApplication>

#include "main_window.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow ventana;
    ventana.show();
    return a.exec();
}