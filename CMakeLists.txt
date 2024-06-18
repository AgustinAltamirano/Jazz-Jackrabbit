cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

# Flags de compilación
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
add_definitions(-DPROJECT_DIR="${PROJECT_SOURCE_DIR}")
add_definitions(-DASSETS_PATH="${PROJECT_SOURCE_DIR}/assets")
add_definitions(-DMAPAS_PATH="${PROJECT_SOURCE_DIR}/src/mapas/")
# add_definitions(-lSDL2main -lSDL2)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(extlib/libSDL2pp)

# Agrega los archivos fuente del juego
add_executable(Client src/client/cliente_main.cpp src/client/juego/cliente.h src/client/juego/cliente.cpp src/client/juego/cliente_enviador.h src/client/juego/cliente_enviador.cpp src/client/juego/cliente_recibidor.h src/client/juego/cliente_recibidor.cpp src/client/juego/cliente_protocolo.h src/client/juego/cliente_protocolo.cpp
        src/client/lobby/lobby.h src/client/lobby/lobby.cpp src/client/lobby/lobby_protocolo.h src/client/lobby/lobby_protocolo.cpp src/client/lobby/lobby_enviador.h src/client/lobby/lobby_enviador.cpp src/client/lobby/lobby_recibidor.h src/client/lobby/lobby_recibidor.cpp
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp
        src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h
        src/client/vista_menu/menu_juego.cpp src/client/vista_menu/menu_juego.h src/client/vista_menu/menu_crear_partida.cpp src/client/vista_menu/menu_crear_partida.h src/client/vista_menu/constantes_menu.h src/client/vista_menu/menu_selec_jugador.cpp src/client/vista_menu/menu_selec_jugador.h src/client/vista_menu/menu_selec_mapa.cpp src/client/vista_menu/menu_selec_mapa.h src/client/vista_menu/sprites_jugador.cpp src/client/vista_menu/sprites_jugador.h src/client/vista_menu/manejador_sprites.cpp src/client/vista_menu/manejador_sprites.h src/client/vista_menu/sprites_mapa.cpp src/client/vista_menu/sprites_mapa.h
        src/client/vista_menu/boton_menu.cpp src/client/vista_menu/boton_menu.h src/client/vista_menu/boton_animado_jugador.cpp src/client/vista_menu/boton_animado_jugador.h src/client/vista_menu/boton_animado_mapa.cpp src/client/vista_menu/boton_animado_mapa.h src/client/vista_menu/menu_principal.cpp src/client/vista_menu/ventana_inicial.cpp assets/menu/resources.qrc
        src/client/vista_menu/ventana_dialogo.cpp src/client/vista_menu/ventana_dialogo.h
        src/client/vista_menu/menu_seleccion.cpp
        src/client/vista_menu/menu_seleccion.h src/common/estado_personaje.h src/common/tipo_arma.h src/common/tipo_bloque_escenario.h src/common/tipo_comando.h src/common/tipo_escenario.h src/common/tipo_personaje.h src/common/comando_validar_dto.cpp src/common/comando_validar_dto.h
        src/client/vista_menu/menu_seleccion.h
        src/common/tipo_enemigo.h
        src/common/tipo_recogible.h
)

add_executable(Server src/server/servidor_main.cpp src/server/servidor.h src/server/servidor.cpp src/server/aceptador.h src/server/aceptador.cpp src/server/comunicador_cliente.h src/server/comunicador_cliente.cpp src/server/enviador_cliente.h src/server/enviador_cliente.cpp src/server/gestor_partidas.h src/server/gestor_partidas.cpp
        src/server/partida.h src/server/partida.cpp src/server/recibidor_cliente.h src/server/recibidor_cliente.cpp src/server/servidor_protocolo.h src/server/servidor_protocolo.cpp
        src/common/comando_dto.h src/common/comando_dto.cpp src/common/comando_crear_dto.h src/common/comando_crear_dto.cpp src/common/comando_unir_dto.h src/common/comando_unir_dto.cpp src/common/snapshot_dto.h src/common/snapshot_dto.cpp
        src/common/config.h src/common/constantes.h src/common/liberror.h src/common/liberror.cpp src/common/queue.h src/common/resolver.h src/common/resolver.cpp src/common/resolvererror.h src/common/resolvererror.cpp src/common/socket.h src/common/socket.cpp src/common/thread.h src/server/logica_juego/personaje.cpp src/server/logica_juego/personaje.h src/server/logica_juego/gameloop.cpp src/server/logica_juego/gameloop.h src/server/logica_juego/manejadorEscenario.cpp src/server/logica_juego/manejadorEscenario.h src/server/logica_juego/assets/bloqueEscenario.cpp src/server/logica_juego/assets/bloqueEscenario.h
        src/server/logica_juego/assets/spawnpoint.h src/client/vista_menu/menu_seleccion.h src/common/estado_personaje.h src/common/tipo_arma.h src/common/tipo_bloque_escenario.h src/common/tipo_comando.h src/common/tipo_escenario.h src/common/tipo_personaje.h src/common/comando_validar_dto.cpp src/common/comando_validar_dto.h
        src/server/logica_juego/assets/recogible.cpp
        src/server/logica_juego/assets/recogible.h
        src/server/logica_juego/assets/bala.h
        src/server/logica_juego/assets/balaInfinita.cpp
        src/server/logica_juego/assets/balaInfinita.h
        src/common/config.cpp
        src/server/logica_juego/assets/bala_arma_1.cpp
        src/server/logica_juego/assets/bala_arma_1.h
        src/server/logica_juego/assets/bala_arma_2.cpp
        src/server/logica_juego/assets/bala_arma_2.h
        src/server/logica_juego/assets/bala_arma_3.cpp
        src/server/logica_juego/assets/bala_arma_3.h
        src/server/logica_juego/enemigo.h
        src/common/validador_de_mapas.cpp
        src/common/validador_de_mapas.h
        src/common/tipo_enemigo.h
        src/common/tipo_recogible.h
        src/server/logica_juego/lagarto.cpp
        src/server/logica_juego/lagarto.h
        src/server/logica_juego/murcielago.cpp
        src/server/logica_juego/murcielago.h
        src/server/logica_juego/esqueleto.cpp
        src/server/logica_juego/esqueleto.h
)

add_subdirectory(src/client/vista_juego)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Busca e incluye las dependencias del proyecto
find_package(yaml-cpp REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)

target_link_libraries(Client PRIVATE vista_juego Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(Server PRIVATE yaml-cpp)

set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR} "/extlib/libSDL2pp")


# Configuración del editor
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(yaml-cpp REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)

set(PROJECT_SOURCES
        src/client/editor/main.cpp
        assets/editor/img/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(.
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET vista_menu APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(editor SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(editor
                ${PROJECT_SOURCES}
                src/client/editor/main_window.cpp
                src/client/editor/main_window.h
                src/client/editor/escena_editor.cpp
                src/client/editor/escena_editor.h
                src/client/editor/constantes.h
                src/client/editor/barra_menu.cpp
                src/client/editor/barra_menu.h
                src/client/editor/lista_botones.cpp
                src/client/editor/lista_botones.h
                src/client/editor/coordenada_punto.h
        )
    endif()
endif()

target_link_libraries(editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia yaml-cpp)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(.)
endif()

