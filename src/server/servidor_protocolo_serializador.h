#ifndef SERVIDOR_PROTOCOLO_SERIALIZADOR_H
#define SERVIDOR_PROTOCOLO_SERIALIZADOR_H


#include <cstdint>
#include <vector>
class ServidorProtocoloSerializador {
public:
    ServidorProtocoloSerializador();

    std::vector<char> serializar_crear_partida(const int32_t& codigo_partida);

    std::vector<char> serializar_error_crear_partida();

    std::vector<char> serializar_unir_partida(const bool& unir);

    std::vector<char> serializar_validar_escenario(const bool& es_valido);

    std::vector<char> serializar_id_cliente(const int32_t& id_cliente);
};


#endif  // SERVIDOR_PROTOCOLO_SERIALIZADOR_H
