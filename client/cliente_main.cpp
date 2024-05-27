#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "juego/cliente.h"
#include "juego/juego.h"
#include "lobby/lobby.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 3) {
            std::cerr << "Esperaba ./client <hostname> <servname>\n";
            return 1;
        }
        const std::string hostname = std::string(argv[1]);
        const std::string servname = std::string(argv[2]);
        Lobby lobby(hostname, servname);
        int32_t id_cliente = lobby.obtener_id_cliente();
        std::cout << "Cliente ID: " << id_cliente << "\n";
        lobby.crear_partida(5);
        std::cout << "Partida creada ID: " << lobby.obtener_crear() << "\n";
        Socket socket = lobby.move_socket();
        Juego juego(id_cliente, socket);
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

