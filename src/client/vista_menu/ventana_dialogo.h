#ifndef VENTANA_DIALOGO_H
#define VENTANA_DIALOGO_H


#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QMainWindow>
#include <QSpinBox>


class MenuCrearPartida;
class MenuPrincipal;


class VentanaDialogo : public QDialog {
public:
    explicit VentanaDialogo(MenuCrearPartida* parent);

    explicit VentanaDialogo(MenuPrincipal* parent);

    VentanaDialogo() = delete;

    int obtener_seleccion();

private:
    QDialogButtonBox button_box;

    QSpinBox spin_box;

    QLabel label;

    void inicializar_ventana(const std::string& titulo, int min_rango,
                             const std::string& clave_yaml, const std::string& texto_label);

    int obtener_max_rango(const std::string& clave);
};


#endif  // VENTANA_DIALOGO_H
