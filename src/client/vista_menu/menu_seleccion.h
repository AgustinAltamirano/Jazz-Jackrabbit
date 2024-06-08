#ifndef MENU_SELECCION_H
#define MENU_SELECCION_H


#include <QBoxLayout>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPushButton>

#define KEY_TIPO_BOTON "tipo_btn"


class MenuSeleccion : public QMainWindow {
public:
    explicit MenuSeleccion(QMainWindow* parent);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    virtual void realizar_accion_menu(int boton_seleccionado) = 0;

    void realizar_accion_clic();

    void conectar_botones(const std::vector<QPushButton*>& botones, const std::vector<int>& props,
                          QBoxLayout& layout);

private:
    QMainWindow* menu_previo;

    QPushButton* boton_enfocado = nullptr;
};


#endif  // MENU_SELECCION_H
