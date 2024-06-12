add_library(logica_juego
        cliente_juego.cpp
        cliente_juego.h
        gameloop.cpp
        gameloop.h
        manejadorEscenario.cpp
        manejadorEscenario.h
        personaje.cpp
        personaje.h
        assets/bala.h
        assets/bala_arma_1.cpp
        assets/bala_arma_1.h
        assets/bala_arma_2.cpp
        assets/bala_arma_2.h
        assets/bala_arma_3.cpp
        assets/bala_arma_3.h
        assets/balaInfinita.cpp
        assets/balaInfinita.h
        assets/bloqueEscenario.cpp
        assets/bloqueEscenario.h
        assets/recogible.cpp
        assets/recogible.h
        assets/spawnpoint.h
        enemigo.h
        enemigo.cpp
        ../../common/config.h
        ../../common/config.cpp
        ../../common/constantes.h
)

find_package(yaml-cpp REQUIRED)

target_link_libraries(logica_juego yaml-cpp)
