#ifndef MANEJADOR_TEXTURAS_H
#define MANEJADOR_TEXTURAS_H


#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>

struct ItemEscena;
class EscenaEditor;


class ListaBotones: public QVBoxLayout {
public:
    ListaBotones(QWidget* parent, EscenaEditor& escena);

    void inicializar_boton_item(ItemEscena item, int posicion);

    void inicializar_boton_texturas(ItemEscena item);

    std::unique_ptr<QGraphicsPixmapItem> obtener_item_seleccionado();

    std::string obtener_tipo_item_seleccionado();

    QPixmap& obtener_imagen_item(const std::string& tipo_item);

    void actualizar_tipo_item_seleccionado(const std::string& nuevo_tipo_item);

    std::string obtener_escenario();

private Q_SLOTS:
    void seleccionar_item();

    void seleccionar_texturas();

private:
    std::map<std::string, ItemEscena> items;

    std::string tipo_item_seleccionado;

    std::string escenario;

    EscenaEditor& escena;

    QPushButton* crear_boton(ItemEscena item);
};


#endif  // MANEJADOR_TEXTURAS_H
