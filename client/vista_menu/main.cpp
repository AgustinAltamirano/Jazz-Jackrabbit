#include <QApplication>
#include "ventana_inicial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaInicial ventana;
    ventana.show();
    return a.exec();
}
