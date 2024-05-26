cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

# Flags de compilación
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DASSETS_PATH="${PROJECT_SOURCE_DIR}/assets")
# add_definitions(-lSDL2main -lSDL2)

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
        client/vista_juego/objeto_animado.h
        client/vista_juego/objeto_animado.cpp
        client/vista_juego/lector_texturas.h
        client/vista_juego/lector_texturas.cpp
        client/vista_juego/administrador_vista_juego.cpp
        client/vista_juego/administrador_vista_juego.h
        client/vista_juego/entrada_juego.cpp
        client/vista_juego/entrada_juego.h
        client/vista_juego/vista_juego_exception.h
        client/vista_juego/personaje.cpp
        client/vista_juego/personaje.h
        client/vista_juego/PersonajeJazz.cpp
        client/vista_juego/PersonajeJazz.h
)

# Busca e incluye las dependencias del proyecto
find_package(yaml-cpp REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2pp REQUIRED)
target_link_libraries(Jazz_Jackrabbit PRIVATE yaml-cpp SDL2pp::SDL2pp)
include_directories(${SDL2_INCLUDE_DIR})
add_subdirectory(extlib/libSDL2pp)

# Configuración de la librería externa libSDL2pp
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support


