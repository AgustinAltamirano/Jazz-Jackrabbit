enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(test_protocolo_lobby
        protocolo/test_protocolo_lobby.cpp
        ../src/client/lobby/lobby_serializador.cpp
)
target_link_libraries(test_protocolo_lobby -lyaml-cpp)

add_executable(test_protocolo_cliente
        protocolo/test_protocolo_cliente.cpp
        ../src/client/juego/cliente_serializador.cpp
)
target_link_libraries(test_protocolo_cliente -lyaml-cpp)

add_executable(test_protocolo_servidor
        protocolo/test_protocolo_cliente.cpp
        ../src/server/servidor_serializador.cpp
        ../src/server/logica_juego/cliente_juego.cpp
        ../src/common/snapshot_dto.cpp
        ../src/common/socket.cpp
        ../src/common/resolver.cpp
)
target_link_libraries(test_protocolo_servidor -lyaml-cpp)

set(test_targets
        test_protocolo_lobby
        test_protocolo_cliente
        test_protocolo_servidor)

foreach (target ${test_targets})
    target_compile_definitions(${target} PUBLIC CONFIG_PATH= "${CMAKE_SOURCE_DIR}/configuracion.yaml")
    add_test(NAME "${target}" COMMAND "${target}")
    add_dependencies(test "${target}")
endforeach ()
