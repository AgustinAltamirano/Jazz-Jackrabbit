#include "lobby.h"
#include <cstring>
#include "../common/comando_crear_dto.h"
#include "../common/comando_unir_dto.h"
#include <sys/socket.h>
#include <utility>
#include <string>
#include <arpa/inet.h>

Lobby::Lobby(const std::string &hostname, const std::string &servname) : socket(hostname.c_str(), servname.c_str()),
                                                                         cola_enviador(1000000),
                                                                         cola_recibidor(1000000), sigo_hablando(true),
                                                                         lobby_enviador(&socket,
                                                                                        std::ref(sigo_hablando),
                                                                                        &cola_enviador),
                                                                         lobby_recibidor(&socket,
                                                                                         std::ref(sigo_hablando),
                                                                                         &cola_recibidor) {
    bool cerrado = false;
    socket.recvall(&id_cliente, sizeof(int), &cerrado);
    id_cliente = ntohl(id_cliente);
    lobby_enviador.start();
    lobby_recibidor.start();
}

bool Lobby::crear_partida(const int8_t &capacidad_partida) {
    return (cola_enviador.try_push(lobby_serializador.serializar_crear_partida(capacidad_partida)));
}

bool Lobby::unir_partida(const int32_t &codigo_partida) {
    return (cola_enviador.try_push(lobby_serializador.serializar_unir_partida(codigo_partida)));
}

void Lobby::comenzar() {
    cola_enviador.try_push(lobby_serializador.serializar_comenzar_jugar());
}

void Lobby::cerrar() {
    sigo_hablando = false;
    socket.shutdown(SHUT_RDWR);
    socket.close();
    cola_enviador.close();
    lobby_enviador.join();
    cola_recibidor.close();
    lobby_recibidor.join();
}

void Lobby::salir_lobby() {
    sigo_hablando = false;
    cola_recibidor.close();
    lobby_enviador.join();
    lobby_recibidor.join();
}

Socket Lobby::move_socket() {
    return std::move(socket);
}

int32_t Lobby::obtener_crear() {
    ComandoDTO *comando_dto = cola_recibidor.pop();
    ComandoCrearDTO *crear_dto = dynamic_cast<ComandoCrearDTO *>(comando_dto);
    int32_t codigo_partida = crear_dto->obtener_codigo_partida();
    delete comando_dto;
    return codigo_partida;
}

bool Lobby::obtener_unir() {
    ComandoDTO *comando_dto = cola_recibidor.pop();
    ComandoUnirDTO *unir_dto = dynamic_cast<ComandoUnirDTO *>(comando_dto);
    bool unio = unir_dto->obtener_unio();
    delete comando_dto;
    return unio;
}

int Lobby::obtener_id_cliente() {
    return id_cliente;
}
