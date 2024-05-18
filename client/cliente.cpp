#include <iostream>
#include <sstream>
#include "cliente_protocolo.h"
#include "cliente.h"

Cliente::Cliente(const std::string &hostname, const std::string &servname) :
        protocolo_cliente(hostname, servname) {}

void Cliente::run() {
    std::string input;
    while (std::getline(std::cin, input)) {
        std::vector<std::string> mensaje = stdin_handler.tokenize_line(input);
        if (mensaje.empty())
            continue;
        if (mensaje.at(0) == "salir") {
            protocolo_cliente.cerrar_conexion();
            return;
        }
        enviar_mensaje(mensaje);
    }
}

void Cliente::enviar_mensaje(std::vector<std::string> &mensaje) {
    if (mensaje[0] == "iniciar") {
        std::uint32_t codigo = protocolo_cliente.iniciar_partida();
        std::cout << "Partida creada: " + std::to_string(codigo) + "\n";
    } else if (mensaje[0] == "enviar") {
        protocolo_cliente.enviar_mensaje(mensaje[1]);
    } else if (mensaje[0] == "unir") {
        std::uint32_t codigo = std::stoul(mensaje[1]);
        std::uint8_t confirmacion = protocolo_cliente.unir_partida(codigo);
        std::string respuesta_confirmacion = (confirmacion == 0) ? "Unido a partida: " : "No existe partida: ";
        std::cout << respuesta_confirmacion + std::to_string(codigo) + "\n";
    } else if (mensaje[0] == "leer") {
        leer_mensajes(std::stoul(mensaje[1]));
    }
}

void Cliente::leer_mensajes(int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        std::cout << "Recibido: " + protocolo_cliente.leer_mensaje() + "\n";
    }
}
