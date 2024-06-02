#include "barra_menu.h"

#include <QFileDialog>
#include <sstream>

#include "constantes.h"


BarraMenu::BarraMenu() : QMenuBar() {
    setFixedSize(ANCHO_PANTALLA, ALTO_MENU_BAR);
    addAction("Guardar", this, &BarraMenu::guardar_mapa);
    addAction("Guardar como", this, &BarraMenu::guardar_como_mapa);
    addAction("Cargar", this, &BarraMenu::cargar_mapa);
}


void BarraMenu::guardar_como_mapa() {
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


void BarraMenu::cargar_mapa() {
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


void BarraMenu::guardar_mapa() {
    if (ruta_mapa_actual.isEmpty()) {
        guardar_como_mapa();
    }
}
