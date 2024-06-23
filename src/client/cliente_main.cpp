#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "juego/cliente.h"
#include "lobby/lobby.h"
#include "vista_juego/administrador_vista_juego.h"
#include "vista_juego/vista_juego_exception.h"
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

        if (not menu.finalizo_correctamente()) {
            lobby.cerrar();
            return 0;
        }

        std::cout << "Cliente ID: " << id_cliente << "\n";
        Socket socket = lobby.move_socket();
        lobby.salir_lobby();
        Cliente cliente(std::move(socket));
        AdministradorVistaJuego admin(id_cliente, "Jazz Jackrabbit 2", cliente);
        admin.run();
        cliente.join();
        return 0;
    } catch (VistaJuegoException& e) {
        std::cerr << "Error de la vista del juego: " << e.what() << std::endl;
        return 1;
    } catch (SDL2pp::Exception& e) {
        std::cerr << "Error de SDL: " << e.GetSDLFunction() << std::endl;
        std::cerr << "Motivo: " << e.GetSDLError() << std::endl;
        return 1;
    } catch (std::exception& err) {
        std::cerr << "Excepcion capturada: " << err.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Excepcion desconocida capturada." << std::endl;
        return 1;
    }
}
