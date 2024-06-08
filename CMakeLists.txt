cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

# Flags de compilación
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
add_definitions(-DPROJECT_DIR="${PROJECT_SOURCE_DIR}")
add_definitions(-DASSETS_PATH= "${PROJECT_SOURCE_DIR}/assets")
# add_definitions(-lSDL2main -lSDL2)

# Agrega los archivos fuente del juego
add_executable(Client src/client/cliente_main.cpp src/client/juego/cliente.h src/client/juego/cliente.cpp src/client/juego/cliente_enviador.h src/client/juego/cliente_enviador.cpp src/client/juego/cliente_recibidor.h src/client/juego/cliente_recibidor.cpp src/client/juego/cliente_serializador.h src/client/juego/cliente_serializador.cpp src/client/juego/cliente_deserializador.h src/client/juego/cliente_deserializador.cpp
        src/client/lobby/lobby.h src/client/lobby/lobby.cpp src/client/lobby/lobby_serializador.h src/client/lobby/lobby_serializador.cpp src/client/lobby/lobby_enviador.h src/client/lobby/lobby_enviador.cpp src/client/lobby/lobby_deserializador.h src/client/lobby/lobby_deserializador.cpp src/client/lobby/lobby_recibidor.h src/client/lobby/lobby_recibidor.cpp
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp src/common/comando_comenzar_dto.h src/common/comando_comenzar_dto.cpp
        src/common/config.h src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h
        src/client/vista_menu/menu_juego.cpp src/client/vista_menu/menu_juego.h src/client/vista_menu/menu_crear_partida.cpp src/client/vista_menu/menu_crear_partida.h src/client/vista_menu/constantes_menu.h src/client/vista_menu/menu_selec_jugador.cpp src/client/vista_menu/menu_selec_jugador.h src/client/vista_menu/menu_selec_mapa.cpp src/client/vista_menu/menu_selec_mapa.h src/client/vista_menu/sprites_jugador.cpp src/client/vista_menu/sprites_jugador.h src/client/vista_menu/manejador_sprites.cpp src/client/vista_menu/manejador_sprites.h src/client/vista_menu/sprites_mapa.cpp src/client/vista_menu/sprites_mapa.h
        src/client/vista_menu/boton_menu.cpp src/client/vista_menu/boton_menu.h src/client/vista_menu/boton_animado_jugador.cpp src/client/vista_menu/boton_animado_jugador.h src/client/vista_menu/boton_animado_mapa.cpp src/client/vista_menu/boton_animado_mapa.h src/client/vista_menu/menu_principal.cpp src/client/vista_menu/ventana_inicial.cpp assets/menu/resources.qrc
        src/client/vista_menu/ventana_dialogo.cpp src/client/vista_menu/ventana_dialogo.h
        src/client/vista_menu/menu_seleccion.cpp
        src/client/vista_menu/menu_seleccion.h src/common/estado_personaje.h src/common/tipo_arma.h src/common/tipo_bloque_escenario.h src/common/tipo_comando.h src/common/tipo_escenario.h src/common/tipo_personaje.h
)

add_executable(Server src/server/servidor_main.cpp src/server/servidor.h src/server/servidor.cpp src/server/aceptador.h src/server/aceptador.cpp src/server/comunicador_cliente.h src/server/comunicador_cliente.cpp src/server/enviador_cliente.h src/server/enviador_cliente.cpp src/server/gestor_partidas.h src/server/gestor_partidas.cpp src/server/logica_juego.h src/server/logica_juego.cpp
        src/server/monitor_partidas.h src/server/monitor_partidas.cpp src/server/monitor_snapshots.h src/server/monitor_snapshots.cpp src/server/partida.h src/server/partida.cpp src/server/recibidor_cliente.h src/server/recibidor_cliente.cpp src/server/servidor_deserializador.h src/server/servidor_deserializador.cpp src/server/servidor_serializador.h src/server/servidor_serializador.cpp
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp src/server/logica_juego/cliente_juego.h src/server/logica_juego/cliente_juego.cpp
        src/common/config.h src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h src/server/logica_juego/personaje.cpp src/server/logica_juego/personaje.h src/server/logica_juego/gameloop.cpp src/server/logica_juego/gameloop.h src/server/logica_juego/manejadorEscenario.cpp src/server/logica_juego/manejadorEscenario.h src/server/logica_juego/assets/bloqueEscenario.cpp src/server/logica_juego/assets/bloqueEscenario.h
        src/server/logica_juego/assets/spawnpoint.h src/client/vista_menu/menu_seleccion.h src/common/estado_personaje.h src/common/tipo_arma.h src/common/tipo_bloque_escenario.h src/common/tipo_comando.h src/common/tipo_escenario.h src/common/tipo_personaje.h)
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp src/common/tipo_comando.h src/server/logica_juego/cliente_juego.h src/server/logica_juego/cliente_juego.cpp
        src/common/config.h src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h src/server/logica_juego/personaje.cpp src/server/logica_juego/personaje.h src/server/logica_juego/gameloop.cpp src/server/logica_juego/gameloop.h src/server/logica_juego/manejadorEscenario.cpp src/server/logica_juego/manejadorEscenario.h src/server/logica_juego/assets/bloqueEscenario.cpp src/server/logica_juego/assets/bloqueEscenario.h src/server/logica_juego/assets/spawnpoint.h
        src/server/logica_juego/assets/recogible.cpp
        src/server/logica_juego/assets/recogible.h
        src/server/logica_juego/assets/bala.h
#        src/server/logica_juego/assets/balaInfinita.cpp
        src/server/logica_juego/assets/balaInfinita.h)

add_subdirectory(src/client/vista_juego)
add_subdirectory(test)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Busca e incluye las dependencias del proyecto
find_package(yaml-cpp REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)

target_link_libraries(Client PRIVATE vista_juego)
target_link_libraries(Server PRIVATE yaml-cpp)
target_link_libraries(Client PRIVATE vista_juego Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(Server PRIVATE yaml-cpp)

add_subdirectory(extlib/libSDL2pp)
add_subdirectory(src/client/editor)
