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
    inicializar_ventana(TITULO_POPUP_JUG, CANT_MIN_JUG, MAX_JUG_YAML,TEXTO_LABEL_JUG);
    connect(&button_box, &QDialogButtonBox::accepted, parent, &MenuCrearPartida::crear_partida);
}


VentanaDialogo::VentanaDialogo(MenuPrincipal* parent) :
        QDialog(parent),
        button_box(this),
        spin_box(this),
        label(this)
{
    inicializar_ventana(TITULO_POPUP_PARTIDA, CANT_MIN_PARTIDAS, MAX_PARTIDAS_YAML,
                        TEXTO_LABEL_PARTIDAS);
    connect(&button_box, &QDialogButtonBox::accepted, parent, &MenuPrincipal::unirse_partida);
}


void VentanaDialogo::inicializar_ventana(const std::string& titulo, int min_rango,
                                         const std::string& clave_yaml,
                                         const std::string& texto_label) {
    setFixedSize(ANCHO_POPUP, ALTO_POPUP);

    button_box.setGeometry(QRect(LEFT_M_BTN_POPUP, TOP_M_BTN_POPUP, ANCHO_BTN_POPUP, ALTO_BTN_POPUP));
    button_box.setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(&button_box, &QDialogButtonBox::clicked, this, &QDialog::close);

    spin_box.setGeometry(QRect(LEFT_M_SPINBOX_POPUP, TOP_M_FILA_POPUP, ANCHO_SPINBOX_POPUP, ALTO_FILA_POPUP));
    label.setGeometry(QRect(LEFT_M_LABEL_POPUP, TOP_M_FILA_POPUP, ANCHO_LABEL_POPUP, ALTO_FILA_POPUP));

    setWindowTitle(titulo.c_str());
    spin_box.setMinimum(min_rango);
    spin_box.setMaximum(obtener_max_rango(clave_yaml));
    
    label.setText(texto_label.c_str());
}


int VentanaDialogo::obtener_seleccion() {
    return spin_box.value();
}


int VentanaDialogo::obtener_max_rango(const std::string& clave) {
    const std::string ruta_yaml = std::string(PROJECT_DIR) + RUTA_CONFIG_YAML;
    YAML::Node yaml_config = YAML::LoadFile(ruta_yaml);
    return yaml_config[clave].as<int>();
}
