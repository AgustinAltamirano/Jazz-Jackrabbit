#include <iostream>

#include "common/config.h"
#include "common/constantes.h"

int main() {
    // Ejemplo de uso del config
    ConfigAdmin& configurador = ConfigAdmin::getInstance();
    // Llamamos a una instancia del configurador (al ser static se crea una instancia y las veces siguientes solo se llama)
    int cant_jugadores_pp = configurador.get(MAX_JUG_POR_PARTIDA);
    std::cout << "maxima cantidad de jugadores: " << cant_jugadores_pp << std::endl;
    return 0;
}
