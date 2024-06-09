#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "juego/cliente.h"
#include "lobby/lobby.h"
#include "vista_menu/menu_juego.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            std::cerr << "Esperaba ./client <hostname> <servname>\n";
            return 1;
        }
        const std::string hostname = std::string(argv[1]);
        const std::string servname = std::string(argv[2]);
        Lobby lobby(hostname, servname);
        int32_t id_cliente = lobby.obtener_id_cliente();
        MenuJuego menu(argc, argv, lobby);
        std::cout << "Cliente ID: " << id_cliente << "\n";
        Socket socket = lobby.move_socket();
        Cliente cliente(std::move(socket));
        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Excepcion capturada: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Excepcion desconocida capturada.\n";
        return 1;
    }
}
