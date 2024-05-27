cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

# Agrega los archivos fuente del juego
add_executable(Client client/cliente_main.cpp client/juego/cliente.h client/juego/cliente.cpp client/juego/juego.h client/juego/juego.cpp client/juego/cliente_enviador.h client/juego/cliente_enviador.cpp client/juego/cliente_recibidor.h client/juego/cliente_recibidor.cpp client/juego/cliente_serializador.h client/juego/cliente_serializador.cpp client/juego/cliente_deserializador.h client/juego/cliente_deserializador.cpp
        client/lobby/lobby.h client/lobby/lobby.cpp client/lobby/lobby_serializador.h client/lobby/lobby_serializador.cpp client/lobby/lobby_enviador.h client/lobby/lobby_enviador.cpp client/lobby/lobby_deserializador.h client/lobby/lobby_deserializador.cpp client/lobby/lobby_recibidor.h client/lobby/lobby_recibidor.cpp
        common/comando_dto.h common/comando_dto.cpp common/comando_crear_dto.h common/comando_crear_dto.cpp common/comando_unir_dto.h common/comando_unir_dto.cpp common/snapshot_dto.h common/snapshot_dto.cpp common/tipo_comando.h common/comando_comenzar_dto.h common/comando_comenzar_dto.cpp
        common/config.h common/constantes.h common/liberror.h common/liberror.cpp common/queue.h common/resolver.h common/resolver.cpp common/resolvererror.h common/resolvererror.cpp common/socket.h common/socket.cpp common/thread.h)

add_executable(Server server/servidor_main.cpp server/servidor.h server/servidor.cpp server/aceptador.h server/aceptador.cpp server/comunicador_cliente.h server/comunicador_cliente.cpp server/enviador_cliente.h server/enviador_cliente.cpp server/gestor_partidas.h server/gestor_partidas.cpp server/logica_juego.h server/logica_juego.cpp
        server/monitor_partidas.h server/monitor_partidas.cpp server/monitor_snapshots.h server/monitor_snapshots.cpp server/partida.h server/partida.cpp server/recibidor_cliente.h server/recibidor_cliente.cpp server/servidor_deserializador.h server/servidor_deserializador.cpp server/servidor_serializador.h server/servidor_serializador.cpp
        common/comando_dto.h common/comando_dto.cpp common/comando_crear_dto.h common/comando_crear_dto.cpp common/comando_unir_dto.h common/comando_unir_dto.cpp common/snapshot_dto.h common/snapshot_dto.cpp common/tipo_comando.h game_logic/cliente_juego.h game_logic/cliente_juego.cpp
        common/config.h common/constantes.h common/liberror.h common/liberror.cpp common/queue.h common/resolver.h common/resolver.cpp common/resolvererror.h common/resolvererror.cpp common/socket.h common/socket.cpp common/thread.h)

#Busca e incluye los yaml-cpp para la configuración
find_package(yaml-cpp REQUIRED)
target_link_libraries(Server PRIVATE yaml-cpp)
