#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "cliente.h"
#include "gameloop.h"
#include "lobby.h"

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
        Socket socket = lobby.move_socket();
        Gameloop juego(id_cliente, socket);
        juego.start();
        lobby.crear_partida(5);
        std::cout << "Partida creada ID: " << lobby.obtener_crear() << "\n";
        return 0;

    } catch (const std::exception &err) {
        std::cerr << "Excepcion capturada: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Excepcion desconocida capturada.\n";
        return 1;
    }

}

