#ifndef GAME_SNAPSHOTDTO_H
#define GAME_SNAPSHOTDTO_H

#include <cstdint>
#include <vector>

#include "../client/vista_juego/snapshot_dto.h"

#include "estado_personaje.h"
#include "tipo_personaje.h"

struct ClienteDTO {
    int32_t id_cliente;
    TipoPersonaje tipo_personaje;
    int32_t pos_x, pos_y;
    bool de_espaldas;
    EstadoPersonaje estado;
    uint32_t vida;
    uint32_t puntos;
    ArmaActual arma_actual;
    int32_t balas_restantes;

    explicit ClienteDTO(iconst uint32_t id_cliente, const TipoPersonaje tipo_personaje,
                        const int32_t pos_x, const int32_t pos_y, const bool de_espaldas,
                        const EstadoPersonaje estado, const uint32_t vida, const uint32_t puntos,
                        const ArmaActual arma_actual, const int32_t balas_restantes):
            id_cliente(id_cliente),
            tipo_personaje(tipo_personaje),
            pos_x(pos_x),
            pos_y(pos_y),
            de_espaldas(de_espaldas),
            estado(estado),
            vida(vida),
            puntos(puntos),
            arma_actual(arma_actual),
            balas_restantes(balas_restantes) {}
};

struct BloqueEscenarioDTO {
    int32_t pos_x, pos_y, angulo;
    uint32_t ancho, alto;
    TipoBloqueEscenario tipo;
    BloqueEscenarioDTO(int32_t pos_x, int32_t pos_y, uint32_t ancho, uint32_t alto, int32_t angulo,
                       TipoEscenario tipo):
            pos_x(pos_x), pos_y(pos_y), ancho(ancho), alto(alto), angulo(angullo), tipo(tipo);
};

class SnapshotDTO {
private:
    TipoEscenario tipo_escenario;
    std::vector<BloqueEscenarioDTO> bloques_escenario;
    std::vector<ClienteDTO> clientes;
    bool fin_juego;

public:
    SnapshotDTO();

    SnapshotDTO(TipoEscenario tipo_escenario);

    SnapshotDTO(std::vector<ClienteDTO> clientes, std::vector<BloqueEscenarioDTO> bloques,
                TipoEscenario tipo_escenario);

    void establecer_tipo_escenario(TipoEscenario tipo_escenario);

    TipoEscenario obtener_tipo_escenario();

    void agregar_cliente(ClienteDTO cliente);

    std::vector<ClienteDTO> obtener_clientes();

    void agregar_bloque_escenario(BloqueEscenarioDTO bloque_escenario);

    std::vector<BloqueEscenarioDTO> obtener_bloques_escenario();

    bool es_fin_juego();

    void establecer_fin_juego(bool fin_juego);
};

#endif
