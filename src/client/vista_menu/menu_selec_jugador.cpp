#include "menu_selec_jugador.h"

#include <QMessageBox>

#include "constantes_menu.h"


MenuSeleccionJugador::MenuSeleccionJugador(QMainWindow* parent, MenuJuego& juego,
                                           bool config):
        MenuSeleccion(parent),
        juego(juego),
        es_de_creacion(config),
        central_widget(this),
        horizontal_layout_widget(&central_widget),
        horizontalLayout(&horizontal_layout_widget),
        jazz_player(this, NUM_JAZZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        spaz_player(this, NUM_SPAZ_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER),
        lori_player(this, NUM_LORI_PLAYER, ANCHO_SEL_PLAYER, ALTO_SEL_PLAYER)
{
    setCentralWidget(&central_widget);

    horizontal_layout_widget.setGeometry(
            QRect(M_LEFT_PLAYER, M_TOP_PLAYER, ANCHO_PANTALLA, ALTO_PANTALLA));

    horizontalLayout.setSpacing(ESPACIADO_ENTRE_JUGADORES);
    horizontalLayout.setContentsMargins(M_LEFT, M_TOP, M_RIGHT, M_BOTTOM);

    conectar_botones({&jazz_player, &spaz_player, &lori_player},
                     {JAZZ, SPAZ, LORI}, horizontalLayout);
}


void MenuSeleccionJugador::realizar_accion_menu(QPushButton* boton_seleccionado) {
    auto opcion_seleccionada = boton_seleccionado->property(KEY_TIPO_BOTON).value<TipoPersonaje>();
    juego.definir_personaje_elegido(opcion_seleccionada);

    if (es_de_creacion) {
        auto codigo_partida = juego.crear_partida();
        std::string codigo_partida_str = std::to_string(codigo_partida);
        QMessageBox msgBox(this);
        msgBox.setText(QString::fromStdString(MSJ_BOX_CREACION_PARTIDA + codigo_partida_str));
        msgBox.setWindowTitle(TITULO_CREACION_PARTIDA);
        msgBox.exec();
    } else {
        auto se_unio_correctamente = juego.unir_partida();
        if (!se_unio_correctamente) {
            QMessageBox msgBox(this);
            msgBox.setText(MSJ_BOX_FALLO_PARTIDA);
            msgBox.setWindowTitle(TITULO_FALLO_PARTIDA);
            msgBox.exec();
            volver_menu_previo();
            return;
        }
    }

    close();
}
