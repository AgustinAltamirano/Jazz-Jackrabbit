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
        vista_juego_exception.h
        ../../common/snapshot_dto.h
        fondo_escenario.cpp
        fondo_escenario.h
        bloque_escenario.cpp
        bloque_escenario.h
        camara.cpp
        camara.h
        vista_juego_defs.h)

# Configuración de las librerías externas SDL2 y SDL2pp
find_package(yaml-cpp REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2 REQUIRED)
find_package(SDL2pp REQUIRED)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

target_link_libraries(vista_juego SDL2pp yaml-cpp)