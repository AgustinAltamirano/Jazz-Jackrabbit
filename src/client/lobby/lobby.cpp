#include "lobby.h"

#include <string>
#include <utility>

#include <sys/socket.h>

#include "comando_crear_dto.h"
#include "comando_unir_dto.h"

Lobby::Lobby(const std::string& hostname, const std::string& servname):
        socket(hostname.c_str(), servname.c_str()),
        cola_enviador(1000000),
        cola_recibidor(1000000),
        sigo_hablando(true),
        lobby_enviador(&socket, std::ref(sigo_hablando), &cola_enviador),
        lobby_recibidor(&socket, std::ref(sigo_hablando), &cola_recibidor),
        lobby_protocolo(&socket) {
    id_cliente = lobby_protocolo.obtener_id_cliente();
    lobby_enviador.start();
    lobby_recibidor.start();
}

int32_t Lobby::crear_partida(const std::string& nombre_escenario, const TipoPersonaje& personaje,
                             const int8_t& capacidad_partida) {
    auto comando_crear = std::make_shared<ComandoCrearDTO>(nombre_escenario, personaje, capacidad_partida);
    cola_enviador.try_push(comando_crear);
    return obtener_respuesta();
}

bool Lobby::unir_partida(const int32_t& codigo_partida, const TipoPersonaje& personaje) {
    auto comando_unir = std::make_shared<ComandoUnirDTO>(codigo_partida, personaje);
    cola_enviador.try_push(comando_unir);
    return obtener_respuesta();
}

bool Lobby::validar_escenario(const std::string& nombre_escenario) {
    auto comando_validar = std::make_shared<ComandoValidarDTO>(nombre_escenario);
    cola_enviador.try_push(comando_validar);
    return obtener_respuesta();
}

void Lobby::cerrar() {
    sigo_hablando = false;
    socket.shutdown(SHUT_RDWR);
    socket.close();
    cola_enviador.close();
    cola_recibidor.close();
    lobby_enviador.join();
    lobby_recibidor.join();
}

void Lobby::salir_lobby() {
    sigo_hablando = false;
    cola_enviador.close();
    cola_recibidor.close();
    lobby_enviador.join();
    lobby_recibidor.join();
}

Socket Lobby::move_socket() { return std::move(socket); }

int32_t Lobby::obtener_respuesta() {
    std::shared_ptr<ComandoDTO> comando_dto = cola_recibidor.pop();
    return comando_dto->obtener_info();
}

int Lobby::obtener_id_cliente() const { return id_cliente; }

bool Lobby::esta_conectado() const { return sigo_hablando; }
