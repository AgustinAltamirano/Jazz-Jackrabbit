#ifndef SNAPSHOT_DTO_H
#define SNAPSHOT_DTO_H

#include <cstdint>
#include <vector>

// Esta clase está definida acá provisoriamente, corresponde que esté en common.

typedef enum {
    JAZZ = 0,
    SPAZ,
    LORI,
} TipoPersonaje;

typedef enum {
    IDLE = 0,
    CORRER,
    DASH,
    DISPARAR_QUIETO,
    SALTAR_ARRIBA,
    SALTAR_ADELANTE,
    CAER_ABAJO,
    CAER_ADELANTE,
    ATAQUE_ESPECIAL,
    INTOXICADO,
    IMPACTADO,
    MUERTE,
} EstadoPersonaje;

typedef enum {
    INFINITA = 0,
    ARMA1,
    ARMA2,
    ARMA3,
} ArmaActual;

typedef enum {
    ESCENARIO_INDEFINIDO = 0,
    ESCENARIO1,
    ESCENARIO2,
} TipoEscenario;

typedef enum {
    PISO = 0,
    TECHO,
    PARED,
    DIAGONAL,
} TipoBloqueEscenario;

struct ClienteDTO {
    uint32_t id_cliente;
    TipoPersonaje tipo_personaje;
    int32_t pos_x, pos_y;
    bool de_espaldas;
    EstadoPersonaje estado;
    uint32_t vida;
    uint32_t puntos;
    ArmaActual arma_actual;
    int32_t balas_restantes;

    ClienteDTO(const uint32_t id_cliente, const TipoPersonaje tipo_personaje, const int32_t pos_x,
               const int32_t pos_y, const bool de_espaldas, const EstadoPersonaje estado,
               const uint32_t vida, const uint32_t puntos, const ArmaActual arma_actual,
               const int32_t balas_restantes):
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
                       TipoEscenario tipo);
};

class SnapshotDTO_provisorio {
private:
    uint32_t id_cliente;
    TipoEscenario tipo_escenario;
    std::vector<BloqueEscenarioDTO> bloques_escenario;
    std::vector<ClienteDTO> clientes;
    bool fin_juego;

public:
    explicit SnapshotDTO_provisorio(const TipoEscenario tipo_escenario):
            id_cliente(0), tipo_escenario(tipo_escenario), fin_juego(false) {}

    void agregar_id_cliente(const uint32_t id_cliente) { this->id_cliente = id_cliente; }

    [[nodiscard]] const uint32_t obtener_id_cliente() const { return id_cliente; }

    [[nodiscard]] TipoEscenario obtener_tipo_escenario() const { return tipo_escenario; }

    void agregar_cliente(ClienteDTO&& cliente) {}

    std::vector<ClienteDTO> obtener_clientes() { return {}; }

    void agregar_bloque_escenario(BloqueEscenarioDTO&& bloque_escenario) {}

    std::vector<BloqueEscenarioDTO> obtener_bloques_escenario() { return {}; }

    [[nodiscard]] bool es_fin_juego() const { return fin_juego; }

    void establecer_fin_juego(bool fin_juego) {}
};

#endif  // SNAPSHOT_DTO_H
