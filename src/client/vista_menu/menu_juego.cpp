#include "menu_juego.h"

#include <QApplication>

#include "ventana_inicial.h"


MenuJuego::MenuJuego(int argc, char* argv[], Lobby& lobby) : lobby(lobby) {
    QApplication a(argc, argv);
    VentanaInicial ventana(*this);
    ventana.show();
    a.exec();
}


void MenuJuego::definir_personaje(int personaje) {
    personaje_elegido = personaje;
}


void MenuJuego::definir_mapa(int mapa) {
    mapa_elegido = mapa;
}


void MenuJuego::definir_cant_jugadores(int8_t cant_jugadores) {
    cant_jugadores_elegidos = cant_jugadores;
}


void MenuJuego::crear_partida() {
    lobby.crear_partida(cant_jugadores_elegidos);
}


void MenuJuego::unir_partida() {
    lobby.unir_partida(codigo_partida);
}


void MenuJuego::definir_codigo_partida(int cod_partida) {
    codigo_partida = cod_partida;
}
