cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

set(CMAKE_CXX_STANDARD 17)

# Agrega los archivos fuente del juego
add_executable(Jazz_Jackrabbit main.cpp
        common/constantes.h
        common/config.h
        common/config.cpp
        common/queue.h
        common/liberror.h
        common/liberror.cpp
        common/resolver.cpp
        common/resolver.h
        common/resolvererror.cpp
        common/resolvererror.h
        common/socket.cpp
        common/socket.h
        common/thread.h
        logica_juego/personaje.cpp
        logica_juego/personaje.h
        logica_juego/gameloop.cpp
        logica_juego/gameloop.h
        logica_juego/manejadorEscenario.cpp
        logica_juego/manejadorEscenario.h
        logica_juego/assets/bloqueEscenario.cpp
        logica_juego/assets/bloqueEscenario.h
        logica_juego/assets/spawnpoint.h)

#Busca e incluye los yaml-cpp para la configuración
find_package(yaml-cpp REQUIRED)
target_link_libraries(Jazz_Jackrabbit PRIVATE yaml-cpp)
