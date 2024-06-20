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

        if (codigo_partida == COD_PARTIDA_INCORRECTA) {
            mostrar_ventana_dialogo(MSJ_BOX_FALLO_CREACION, TITULO_FALLO_CREACION);
            return;
        }

        std::string codigo_partida_str = std::to_string(codigo_partida);
        mostrar_ventana_dialogo(MSJ_BOX_CREACION_PARTIDA + codigo_partida_str, TITULO_CREACION_PARTIDA);
    } else {
        auto se_unio_correctamente = juego.unir_partida();
        if (!se_unio_correctamente) {
            mostrar_ventana_dialogo(MSJ_BOX_FALLO_PARTIDA, TITULO_FALLO_PARTIDA);
            volver_menu_previo();
            return;
        }
    }

    close();
}


void MenuSeleccionJugador::mostrar_ventana_dialogo(const std::string& mensaje,
                                                   const std::string& titulo) {
    QMessageBox msgBox(this);
    msgBox.setText(mensaje.c_str());
    msgBox.setWindowTitle(titulo.c_str());
    msgBox.exec();
}
