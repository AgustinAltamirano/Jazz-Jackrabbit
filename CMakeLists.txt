cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

# Flags de compilación
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
add_definitions(-DASSETS_PATH="${PROJECT_SOURCE_DIR}/assets")
# add_definitions(-lSDL2main -lSDL2)

# Agrega los archivos fuente del juego
add_executable(Client src/client/cliente_main.cpp src/client/juego/cliente.h src/client/juego/cliente.cpp src/client/juego/juego.h src/client/juego/juego.cpp src/client/juego/cliente_enviador.h src/client/juego/cliente_enviador.cpp src/client/juego/cliente_recibidor.h src/client/juego/cliente_recibidor.cpp src/client/juego/cliente_serializador.h src/client/juego/cliente_serializador.cpp src/client/juego/cliente_deserializador.h src/client/juego/cliente_deserializador.cpp
        src/client/lobby/lobby.h src/client/lobby/lobby.cpp src/client/lobby/lobby_serializador.h src/client/lobby/lobby_serializador.cpp src/client/lobby/lobby_enviador.h src/client/lobby/lobby_enviador.cpp src/client/lobby/lobby_deserializador.h src/client/lobby/lobby_deserializador.cpp src/client/lobby/lobby_recibidor.h src/client/lobby/lobby_recibidor.cpp
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp src/common/tipo_comando.h src/common/comando_comenzar_dto.h src/common/comando_comenzar_dto.cpp
        src/common/config.h src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h src/client/vista_juego/objeto_animado.h
        src/client/vista_juego/objeto_animado.cpp
        src/client/vista_juego/lector_texturas.h
        src/client/vista_juego/lector_texturas.cpp
        src/client/vista_juego/administrador_vista_juego.cpp
        src/client/vista_juego/administrador_vista_juego.h)

add_executable(Server src/server/servidor_main.cpp src/server/servidor.h src/server/servidor.cpp src/server/aceptador.h src/server/aceptador.cpp src/server/comunicador_cliente.h src/server/comunicador_cliente.cpp src/server/enviador_cliente.h src/server/enviador_cliente.cpp src/server/gestor_partidas.h src/server/gestor_partidas.cpp src/server/logica_juego.h src/server/logica_juego.cpp
        src/server/monitor_partidas.h src/server/monitor_partidas.cpp src/server/monitor_snapshots.h src/server/monitor_snapshots.cpp src/server/partida.h src/server/partida.cpp src/server/recibidor_cliente.h src/server/recibidor_cliente.cpp src/server/servidor_deserializador.h src/server/servidor_deserializador.cpp src/server/servidor_serializador.h src/server/servidor_serializador.cpp
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp src/common/tipo_comando.h src/server/game_logic/cliente_juego.h src/server/game_logic/cliente_juego.cpp
        src/common/config.h src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h src/server/logica_juego/personaje.cpp src/server/logica_juego/personaje.h src/server/logica_juego/gameloop.cpp src/server/logica_juego/gameloop.h src/server/logica_juego/manejadorEscenario.cpp src/server/logica_juego/manejadorEscenario.h src/server/logica_juego/assets/bloqueEscenario.cpp src/server/logica_juego/assets/bloqueEscenario.h src/server/logica_juego/assets/spawnpoint.h)

# Busca e incluye las dependencias del proyecto
find_package(yaml-cpp REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2pp REQUIRED)
target_link_libraries(Client PRIVATE yaml-cpp SDL2pp::SDL2pp)
target_link_libraries(Server PRIVATE yaml-cpp)
include_directories(${SDL2_INCLUDE_DIR})
add_subdirectory(extlib/libSDL2pp)

# Configuración de la librería externa libSDL2pp
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

add_subdirectory(src/client/vista_menu)
