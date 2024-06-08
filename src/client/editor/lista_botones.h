#ifndef MANEJADOR_TEXTURAS_H
#define MANEJADOR_TEXTURAS_H


#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>
#include "constantes.h"

class EscenaEditor;


class ListaBotones: public QVBoxLayout {
public:
    ListaBotones(QWidget* parent, EscenaEditor& escena);

    void inicializar_boton_item(ItemEscena item, int posicion);

    void inicializar_boton_texturas(ItemEscena item);

    [[nodiscard]] std::unique_ptr<QGraphicsPixmapItem> obtener_item_seleccionado() const;

    QPixmap& obtener_imagen_item(TipoItemEditor tipo, TipoEscenarioEditor texturas);

    void actualizar_item_seleccionado(TipoItemEditor tipo, TipoEscenarioEditor texturas);

    TipoEscenarioEditor obtener_escenario();

private Q_SLOTS:
    void seleccionar_item();

    void seleccionar_texturas();

private:
    std::map<std::pair<TipoItemEditor, TipoEscenarioEditor>, ItemEscena> items;

    ItemEscena item_seleccionado;

    TipoEscenarioEditor escenario;

    EscenaEditor& escena;

    QPushButton* crear_boton(ItemEscena item);
};


#endif  // MANEJADOR_TEXTURAS_H
