#ifndef GAME_SNAPSHOTDTO_H
#define GAME_SNAPSHOTDTO_H

#include <cstdint>
#include <vector>

struct ClienteDTO {
    int32_t id_cliente;

    ClienteDTO(int32_t id_cliente) : id_cliente(id_cliente) {}
};

class SnapshotDTO {
private:

    std::vector<ClienteDTO> clientes;

    bool fin_juego;

public:
    SnapshotDTO();

    SnapshotDTO(std::vector<ClienteDTO> clientes);

    void agregar_cliente(ClienteDTO cliente);

    std::vector<ClienteDTO> obtener_clientes();

    bool es_fin_juego() const;

    void establecer_fin_juego(bool fin_juego);
};

#endif
