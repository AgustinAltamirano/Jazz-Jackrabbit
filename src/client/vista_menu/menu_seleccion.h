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

    void enfocar(QPushButton* boton);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    virtual void realizar_accion_menu(QPushButton* boton_seleccionado) = 0;

    void realizar_accion_clic();

    void conectar_botones(const std::vector<QPushButton*>& botones, const std::vector<int>& props,
                          QBoxLayout& layout);

    void volver_menu_previo();

private:
    QMainWindow* menu_previo;

    QPushButton* boton_enfocado = nullptr;

    void desenfocar_boton();
};


#endif  // MENU_SELECCION_H
