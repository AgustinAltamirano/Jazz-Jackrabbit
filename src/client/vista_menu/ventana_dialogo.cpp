#include "ventana_dialogo.h"

#include <QAbstractButton>

#include <yaml-cpp/yaml.h>

#include "constantes_menu.h"
#include "menu_principal.h"


VentanaDialogo::VentanaDialogo(MenuCrearPartida* parent) :
        QDialog(parent),
        button_box(this),
        spin_box(this),
        label(this) {
    inicializar_ventana(TITULO_POPUP_JUG, TEXTO_LABEL_JUG);
    inicializar_spin_box(CANT_MIN_JUG, MAX_JUG_YAML);
    connect(&button_box, &QDialogButtonBox::accepted, parent, &MenuCrearPartida::crear_partida);
}


VentanaDialogo::VentanaDialogo(MenuPrincipal* parent) :
        QDialog(parent),
        button_box(this),
        spin_box(this),
        label(this)
{
    inicializar_ventana(TITULO_POPUP_PARTIDA, TEXTO_LABEL_PARTIDAS);
    inicializar_spin_box(CANT_MIN_PARTIDAS, MAX_PARTIDAS_YAML);
    connect(&button_box, &QDialogButtonBox::accepted, parent, &MenuPrincipal::unirse_partida);
}


VentanaDialogo::VentanaDialogo(MenuSeleccionMapa* parent) :
        QDialog(parent),
        button_box(this),
        input_mapa(this),
        label(this)
{
    inicializar_ventana("Ingresar mapa", "Nombre del mapa:");
    inicializar_line_edit();
    connect(&button_box, &QDialogButtonBox::accepted, parent, &MenuSeleccionMapa::validar_seleccion_mapa);
    connect(&button_box, &QDialogButtonBox::rejected, &input_mapa, &QLineEdit::clear);
}


void VentanaDialogo::inicializar_ventana(const std::string& titulo, const std::string& texto_label) {
    setFixedSize(ANCHO_POPUP, ALTO_POPUP);

    button_box.setGeometry(QRect(LEFT_M_BTN_POPUP, TOP_M_BTN_POPUP, ANCHO_BTN_POPUP, ALTO_BTN_POPUP));
    button_box.setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(&button_box, &QDialogButtonBox::clicked, this, &QDialog::close);

    label.setGeometry(QRect(LEFT_M_LABEL_POPUP, TOP_M_FILA_POPUP, ANCHO_LABEL_POPUP, ALTO_FILA_POPUP));

    setWindowTitle(titulo.c_str());
    
    label.setText(texto_label.c_str());
}


void VentanaDialogo::inicializar_spin_box(int min_rango, const std::string& clave_yaml) {
    spin_box.setGeometry(QRect(LEFT_M_SPINBOX_POPUP, TOP_M_FILA_POPUP, ANCHO_SPINBOX_POPUP, ALTO_FILA_POPUP));
    spin_box.setMinimum(min_rango);
    spin_box.setMaximum(obtener_max_rango(clave_yaml));
}


void VentanaDialogo::inicializar_line_edit() {
    input_mapa.setGeometry(QRect(LEFT_M_LABEL_POPUP, TOP_M_FILA_POPUP, 200, ALTO_FILA_POPUP));
    input_mapa.setPlaceholderText("Nombre del mapa");
}


int VentanaDialogo::obtener_seleccion() {
    return spin_box.value();
}


std::string VentanaDialogo::obtener_seleccion_mapa() {
    auto mapa = input_mapa.text().toStdString();
    return mapa;
}


void VentanaDialogo::limpiar_seleccion() {
    input_mapa.clear();
}

int VentanaDialogo::obtener_max_rango(const std::string& clave) {
    const std::string ruta_yaml = std::string(PROJECT_DIR) + RUTA_CONFIG_YAML;
    YAML::Node yaml_config = YAML::LoadFile(ruta_yaml);
    return yaml_config[clave].as<int>();
}
