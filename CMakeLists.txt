cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

# Flags de compilación
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DASSETS_PATH="assets")
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
)

# Busca e incluye los yaml-cpp para la configuración
find_package(yaml-cpp REQUIRED)
target_link_libraries(Jazz_Jackrabbit PRIVATE yaml-cpp)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Configuración de la librería externa libSDL2pp
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(extlib/libSDL2pp)
