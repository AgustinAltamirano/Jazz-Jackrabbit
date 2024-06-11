#ifndef VENTANA_DIALOGO_H
#define VENTANA_DIALOGO_H


#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSpinBox>


class MenuCrearPartida;
class MenuPrincipal;
class MenuSeleccionMapa;


class VentanaDialogo : public QDialog {
public:
    explicit VentanaDialogo(MenuCrearPartida* parent);

    explicit VentanaDialogo(MenuPrincipal* parent);

    explicit VentanaDialogo(MenuSeleccionMapa* parent);

    VentanaDialogo() = delete;

    int obtener_seleccion();

    std::string obtener_seleccion_mapa();

private:
    QDialogButtonBox button_box;

    QSpinBox spin_box;

    QLabel label;

    QLineEdit input_mapa;

    void inicializar_ventana(const std::string& titulo, const std::string& texto_label);

    void inicializar_spin_box(int min_rango, const std::string& clave_yaml);

    void inicializar_line_edit();

    int obtener_max_rango(const std::string& clave);
};


#endif  // VENTANA_DIALOGO_H
