#ifndef MANEJADOR_TEXTURAS_H
#define MANEJADOR_TEXTURAS_H


#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>


class ListaBotones: public QVBoxLayout {
public:
    explicit ListaBotones(QWidget* parent, QGraphicsView& escena);

    void inicializar_boton_item(QPixmap imagen_item,
                                const std::string& tipo_item,
                                const std::string& mapa_asociado,
                                int posicion);

    void inicializar_boton_texturas(QPixmap& imagen_fondo, const std::string& nombre_mapa);

    QPixmap& obtener_imagen_item_seleccionado();

    std::string obtener_tipo_item_seleccionado();

private Q_SLOTS:
    void seleccionar_item();

    void seleccionar_texturas();

private:
    std::map<std::string, QPixmap> items;

    std::map<std::string, std::vector<std::unique_ptr<QPushButton>>> items_por_mapa;

    std::string tipo_item_seleccionado;

    QGraphicsView& escena;

    std::unique_ptr<QPushButton> crear_boton(QPixmap& imagen_item, const std::string& tipo_item);
};


#endif  // MANEJADOR_TEXTURAS_H
