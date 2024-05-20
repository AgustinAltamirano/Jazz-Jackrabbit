#include <iostream>

#include "client/vista_juego/administrador_vista_juego.h"
#include "common/config.h"
#include "common/constantes.h"

int main() {
    // Ejemplo de uso del config
    ConfigAdmin
            configurador;  // Creamos el configurador (sin parentesis porque no lleva argumentos)
    int cant_jugadores_pp = configurador.get(MAX_JUG_POR_PARTIDA);
    std::cout << "maxima cantidad de jugadores: " << cant_jugadores_pp << std::endl;

    // Ejemplo de uso de SDL
    AdministradorVistaJuego admin("Test");
    admin.run();
    return 0;
}
