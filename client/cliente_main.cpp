#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "cliente.h"
#include "gameloop.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 3) {
            std::cerr << "Esperaba ./client <hostname> <servname>\n";
            return 1;
        }
        const std::string hostname = std::string(argv[1]);
        const std::string servname = std::string(argv[2]);
        Gameloop juego(hostname, servname);
        juego.start();
        return 0;

    } catch (const std::exception &err) {
        std::cerr << "Excepcion capturada: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Excepcion desconocida capturada.\n";
        return 1;
    }

}

