#include <string>
#include <iostream>
#include <vector>
#include "servidor.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Esperaba ./server <port>\n";
            return 1;
        }
        Servidor servidor(argv[1]);
        servidor.run();
        return 0;
    } catch (const std::exception &err) {
        std::cerr << "Excepcion capturada: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Excepcion desconocida capturada.\n";
        return 1;
    }

}


