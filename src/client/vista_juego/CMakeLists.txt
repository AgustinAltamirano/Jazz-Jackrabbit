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
        vista_juego_defs.h
        hud.cpp
        hud.h
        ../../common/tipo_enemigo.h
        ../../common/tipo_recogible.h
        admin_enemigos.cpp
        admin_enemigos.h
        admin_balas.cpp
        admin_balas.h
        admin_recogibles.cpp
        admin_recogibles.h
        top_jugadores.cpp
        top_jugadores.h
        reproductor_musica.cpp
        reproductor_musica.h
        reproductor_sonido.cpp
        reproductor_sonido.h)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

# Configuración de las librerías externas SDL2 y SDL2pp
find_package(yaml-cpp REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2 REQUIRED)
find_package(SDL2pp REQUIRED)

target_link_libraries(vista_juego SDL2pp::SDL2pp yaml-cpp)