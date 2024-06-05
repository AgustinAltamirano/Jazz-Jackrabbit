#ifndef MANEJADOR_TEXTURAS_H
#define MANEJADOR_TEXTURAS_H


#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>

class EscenaEditor;


class ListaBotones: public QVBoxLayout {
public:
    explicit ListaBotones(QWidget* parent, QGraphicsView& vista_escena, EscenaEditor& escena);

    void inicializar_boton_item(QPixmap& imagen_item,
                                const std::string& tipo_item,
                                const std::string& mapa_asociado,
                                int posicion);

    void inicializar_boton_texturas(QPixmap& imagen_fondo, const std::string& nombre_mapa);

    QPixmap& obtener_imagen_item_seleccionado();

    std::string obtener_tipo_item_seleccionado();

    QPixmap& obtener_imagen_item(const std::string& tipo_item);

    std::string obtener_mapa_item(const std::string& tipo_item);

    void actualizar_tipo_item_seleccionado(const std::string& nuevo_tipo_item);

private Q_SLOTS:
    void seleccionar_item();

    void seleccionar_texturas();

private:
    std::map<std::string, QPixmap> items;

    std::map<std::string, std::string> items_por_mapa;

    std::map<std::string, std::vector<std::unique_ptr<QPushButton>>> botones_por_mapa;

    std::string tipo_item_seleccionado;

    EscenaEditor& escena;

    QGraphicsView& vista_escena;

    std::unique_ptr<QPushButton> crear_boton(QPixmap& imagen_item, const std::string& tipo_item);
};


#endif  // MANEJADOR_TEXTURAS_H
