#ifndef GAME_SNAPSHOTDTO_H
#define GAME_SNAPSHOTDTO_H

#include <cstdint>
#include <vector>

#include "../server/logica_juego/assets/bloqueEscenario.h"

#include "estado_personaje.h"
#include "tipo_arma.h"
#include "tipo_bloque_escenario.h"
#include "tipo_escenario.h"
#include "tipo_personaje.h"

struct ClienteDTO {
    int32_t id_cliente;
    TipoPersonaje tipo_personaje;
    int32_t pos_x, pos_y;
    bool de_espaldas;
    EstadoPersonaje estado;
    uint32_t vida;
    uint32_t puntos;
    TipoArma arma_actual;
    int32_t balas_restantes;
    ClienteDTO(int32_t id_cliente, TipoPersonaje tipo_personaje, int32_t pos_x, int32_t pos_y,
               bool de_espaldas, EstadoPersonaje estado, uint32_t vida, uint32_t puntos,
               TipoArma arma_actual, int32_t balas_restantes):
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
    ClienteDTO() :
            id_cliente(),
            tipo_personaje(),
            pos_x(),
            pos_y(),
            de_espaldas(),
            estado(),
            vida(),
            puntos(),
            arma_actual(),
            balas_restantes() {}
} __attribute__((packed));

struct BloqueEscenarioDTO {
    int32_t pos_x, pos_y, angulo;
    uint32_t ancho, alto;
    TipoBloqueEscenario tipo;
    BloqueEscenarioDTO(int32_t pos_x, int32_t pos_y, uint32_t ancho, uint32_t alto, int32_t angulo,
                       TipoBloqueEscenario tipo):
            pos_x(pos_x), pos_y(pos_y), ancho(ancho), alto(alto), angulo(angulo), tipo(tipo) {}
    BloqueEscenarioDTO():
            pos_x(), pos_y(), ancho(), alto(), angulo(), tipo() {}
} __attribute__((packed));

class SnapshotDTO {
private:
    TipoEscenario tipo_escenario;
    std::vector<BloqueEscenarioDTO> bloques_escenario;
    std::vector<ClienteDTO> clientes;
    bool fin_juego;

public:
    SnapshotDTO();

    explicit SnapshotDTO(TipoEscenario tipo_escenario);

    SnapshotDTO(std::vector<ClienteDTO> clientes, std::vector<BloqueEscenarioDTO> bloques,
                TipoEscenario tipo_escenario);

    void establecer_tipo_escenario(TipoEscenario tipo_escenario);

    TipoEscenario obtener_tipo_escenario();

    void agregar_cliente(ClienteDTO cliente);

    std::vector<ClienteDTO>& obtener_clientes();

    void agregar_bloque_escenario(BloqueEscenarioDTO bloque_escenario);

    std::vector<BloqueEscenarioDTO>& obtener_bloques_escenario();

    bool es_fin_juego();

    void establecer_fin_juego(bool fin_juego);
};

#endif
