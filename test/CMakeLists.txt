enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(test_protocolo_lobby
        protocolo/test_protocolo_lobby.cpp
        ../src/client/lobby/lobby_protocolo.cpp
        ../src/client/lobby/comando_dto.cpp
        ../src/client/lobby/comando_crear_dto.cpp
        ../src/client/lobby/comando_unir_dto.cpp
        ../src/client/lobby/comando_validar_dto.cpp
        ../src/common/tipo_comando.h
        ../src/common/socket_abstracto.h
        ../src/common/socket_dummy.cpp
        ../src/common/tipo_personaje.h
        ../src/server/servidor_protocolo_serializador.cpp
)
target_link_libraries(test_protocolo_lobby -lyaml-cpp)

add_executable(test_protocolo_cliente
        protocolo/test_protocolo_cliente.cpp
        ../src/client/juego/cliente_protocolo.cpp
        ../src/common/snapshot_dto.cpp
        ../src/common/tipo_comando.h
        ../src/common/socket_abstracto.h
        ../src/common/socket_dummy.cpp
        ../src/server/servidor_protocolo_serializador.cpp
)
target_link_libraries(test_protocolo_cliente -lyaml-cpp)

add_executable(test_protocolo_servidor
        protocolo/test_protocolo_servidor.cpp
        ../src/server/servidor_protocolo.cpp
        ../src/server/servidor_protocolo_serializador.cpp
        ../src/server/comando_server.h
        ../src/server/comando_server.cpp
        ../src/server/comando_server_generico.cpp
        ../src/server/comando_server_crear.cpp
        ../src/server/comando_server_unir.cpp
        ../src/server/comando_server_validar.cpp
        ../src/common/validador_de_mapas.cpp
        ../src/server/gestor_partidas.cpp
        ../src/server/partida.cpp
        ../src/server/logica_juego/gameloop.cpp
        ../src/server/logica_juego/manejadorEscenario.cpp
        ../src/server/logica_juego/personaje.cpp
        ../src/server/logica_juego/murcielago.cpp
        ../src/server/logica_juego/lagarto.cpp
        ../src/server/logica_juego/esqueleto.cpp
        ../src/server/logica_juego/enemigo.h
        ../src/server/logica_juego/assets/bala.h
        ../src/server/logica_juego/assets/bala_arma_1.cpp
        ../src/server/logica_juego/assets/bala_arma_2.cpp
        ../src/server/logica_juego/assets/bala_arma_3.cpp
        ../src/server/logica_juego/assets/balaInfinita.cpp
        ../src/server/logica_juego/assets/bloqueEscenario.cpp
        ../src/server/logica_juego/assets/recogible.cpp
        ../src/server/logica_juego/assets/spawnpoint.h
        ../src/common/snapshot_dto.cpp
        ../src/common/config.cpp
        ../src/common/socket_abstracto.h
        ../src/common/socket_dummy.cpp
        ../src/common/resolver.cpp
        ../src/common/liberror.cpp
        ../src/common/resolvererror.cpp
)
target_link_libraries(test_protocolo_servidor -lyaml-cpp)

add_executable(test_protocolo_snapshot
        protocolo/test_protocolo_snapshot.cpp
        ../src/client/juego/cliente_protocolo.cpp
        ../src/server/servidor_protocolo.cpp
        ../src/server/servidor_protocolo_serializador.cpp
        ../src/server/comando_server.h
        ../src/server/comando_server.cpp
        ../src/server/comando_server_generico.cpp
        ../src/server/comando_server_crear.cpp
        ../src/server/comando_server_unir.cpp
        ../src/server/comando_server_validar.cpp
        ../src/common/validador_de_mapas.cpp
        ../src/server/gestor_partidas.cpp
        ../src/server/partida.cpp
        ../src/server/logica_juego/gameloop.cpp
        ../src/server/logica_juego/manejadorEscenario.cpp
        ../src/server/logica_juego/personaje.cpp
        ../src/server/logica_juego/murcielago.cpp
        ../src/server/logica_juego/lagarto.cpp
        ../src/server/logica_juego/esqueleto.cpp
        ../src/server/logica_juego/enemigo.h
        ../src/server/logica_juego/assets/bala.h
        ../src/server/logica_juego/assets/bala_arma_1.cpp
        ../src/server/logica_juego/assets/bala_arma_2.cpp
        ../src/server/logica_juego/assets/bala_arma_3.cpp
        ../src/server/logica_juego/assets/balaInfinita.cpp
        ../src/server/logica_juego/assets/bloqueEscenario.cpp
        ../src/server/logica_juego/assets/recogible.cpp
        ../src/server/logica_juego/assets/spawnpoint.h
        ../src/common/snapshot_dto.cpp
        ../src/common/config.cpp
        ../src/common/socket_abstracto.h
        ../src/common/socket_dummy.cpp
        ../src/common/resolver.cpp
        ../src/common/liberror.cpp
        ../src/common/resolvererror.cpp
)
target_link_libraries(test_protocolo_snapshot -lyaml-cpp)

set(test_targets
        test_protocolo_lobby
        test_protocolo_cliente
        test_protocolo_servidor
        test_protocolo_snapshot)

foreach (target ${test_targets})
    target_compile_definitions(${target} PUBLIC CONFIG_PATH=\"${CMAKE_SOURCE_DIR}/configuracion.yaml\")
    add_test(NAME "${target}" COMMAND "${target}")
    add_dependencies(test "${target}")
endforeach ()
