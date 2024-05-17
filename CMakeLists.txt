cmake_minimum_required(VERSION 3.22)
project(Jazz_Jackrabbit)

set(CMAKE_CXX_STANDARD 17)

# Agrega los archivos fuente del juego
add_executable(Jazz_Jackrabbit main.cpp
        common/constantes.h
        common/config.h
        common/config.cpp)

#Busca e incluye los yaml-cpp para la configuración
find_package(yaml-cpp REQUIRED)
target_link_libraries(Jazz_Jackrabbit PRIVATE yaml-cpp)

# Configuración de la librería externa libSDL2pp
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(extlib/libSDL2pp)
