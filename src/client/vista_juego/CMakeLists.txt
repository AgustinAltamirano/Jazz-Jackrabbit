add_library(vista_juego
        administrador_vista_juego.cpp
        administrador_vista_juego.h
        entrada_juego.cpp
        entrada_juego.h
        lector_texturas.cpp
        lector_texturas.h
        objeto_animado.cpp
        objeto_animado.h
        personaje.cpp
        personaje.h
        personaje_jazz.cpp
        personaje_jazz.h
        personaje_lori.cpp
        personaje_lori.h
        personaje_spaz.cpp
        personaje_spaz.h
        vista_juego_exception.h)

# Configuración de las librerías externas SDL2 y SDL2pp
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2 REQUIRED)
find_package(SDL2pp REQUIRED)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

target_link_libraries(vista_juego SDL2pp::SDL2pp)