#include "menu_juego.h"

#include <QApplication>

#include "ventana_inicial.h"


MenuJuego::MenuJuego(int argc, char* argv[], Lobby& lobby) :
        lobby(lobby), personaje_elegido(), mapa_elegido(), cant_jugadores(0), codigo_partida(0) {
    QApplication a(argc, argv);
    VentanaInicial ventana(*this);
    ventana.show();
    a.exec();
}


void MenuJuego::definir_personaje_elegido(TipoPersonaje personaje) {
    personaje_elegido = personaje;
}


void MenuJuego::definir_mapa_elegido(const std::string& mapa) {
    mapa_elegido = mapa;
}


void MenuJuego::definir_cant_jugadores(int cant_jug) { cant_jugadores = cant_jug; }


int32_t MenuJuego::crear_partida() {
    auto cod_partida = lobby.crear_partida(mapa_elegido, personaje_elegido, cant_jugadores);
    if (cod_partida != COD_PARTIDA_INCORRECTA) {
        ultima_accion_correcta = true;
    }
    return cod_partida;
}


bool MenuJuego::unir_partida() {
    ultima_accion_correcta = lobby.unir_partida(codigo_partida, personaje_elegido);
    return ultima_accion_correcta;
}


void MenuJuego::definir_codigo_partida(int cod_partida) {
    codigo_partida = cod_partida;
}


bool MenuJuego::validar_mapa_elegido(const std::string& mapa) {
    return lobby.validar_escenario(mapa);
}


bool MenuJuego::finalizo_correctamente() const { return ultima_accion_correcta; }


bool MenuJuego::esta_conectado() { return lobby.esta_conectado(); }
