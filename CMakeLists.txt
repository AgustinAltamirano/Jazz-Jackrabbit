cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

# Agrega los archivos fuente del juego
add_executable(Client client/cliente_main.cpp client/cliente.h client/cliente.cpp client/cliente_protocolo.h client/cliente_protocolo.cpp client/stdin_handler.cpp client/stdin_handler.h
        common/liberror.h common/liberror.cpp common/resolver.cpp common/resolver.h common/resolvererror.h common/resolvererror.cpp common/socket.h common/socket.cpp common/thread.h common/queue.h)

add_executable(Server server/servidor_main.cpp server/servidor.h server/servidor.cpp server/aceptador_cliente.h server/aceptador_cliente.cpp server/monitor_partidas.cpp server/monitor_partidas.h
        server/monitor_partida.cpp server/monitor_partida.h server/comunicador_cliente.cpp server/comunicador_cliente.h server/juego.cpp server/juego.h server/recibidor_cliente.cpp server/recibidor_cliente.h
        server/servidor_protocolo.h server/servidor_protocolo.cpp common/liberror.h common/liberror.cpp common/resolver.cpp common/resolver.h common/resolvererror.h common/resolvererror.cpp
        common/socket.h common/socket.cpp common/thread.h common/queue.h common/constantes.h common/config.h common/config.cpp)

#Busca e incluye los yaml-cpp para la configuracion
find_package(yaml-cpp REQUIRED)
target_link_libraries(Server PRIVATE yaml-cpp)
