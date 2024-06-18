#ifndef GAME_SNAPSHOTDTO_H
#define GAME_SNAPSHOTDTO_H

#include <cstdint>
#include <vector>

#include "../server/logica_juego/assets/bloqueEscenario.h"

#include "estado_personaje.h"
#include "tipo_arma.h"
#include "tipo_bloque_escenario.h"
#include "tipo_enemigo.h"
#include "tipo_escenario.h"
#include "tipo_personaje.h"
#include "tipo_recogible.h"

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
    ClienteDTO():
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
    BloqueEscenarioDTO(): pos_x(), pos_y(), ancho(), alto(), angulo(), tipo() {}
} __attribute__((packed));

struct BalaDTO {
    int32_t pos_x, pos_y;
    TipoArma tipo;
    bool choco;
    BalaDTO(int32_t pos_x, int32_t pos_y, TipoArma tipo, bool choco):
            pos_x(pos_x), pos_y(pos_y), tipo(tipo), choco(choco) {}
    BalaDTO(): pos_x(), pos_y(), tipo(), choco(false) {}
} __attribute__((packed));

struct EnemigoDTO {
    int32_t id, pos_x, pos_y, alto, ancho;
    TipoEnemigo tipo;
    bool invertido;
    EnemigoDTO(int32_t id, int32_t pos_x, int32_t pos_y, int32_t alto, int32_t ancho,
               TipoEnemigo tipo, bool invertido):
            id(id),
            pos_x(pos_x),
            pos_y(pos_y),
            alto(alto),
            ancho(ancho),
            tipo(tipo),
            invertido(invertido) {}
    EnemigoDTO(): id(), pos_x(), pos_y(), alto(), ancho(), tipo(), invertido() {}
} __attribute__((packed));

struct RecogibleDTO {
    int32_t pos_x, pos_y, alto, ancho;
    TipoRecogible tipo;
    RecogibleDTO(int32_t pos_x, int32_t pos_y, int32_t alto, int32_t ancho, TipoRecogible tipo):
            pos_x(pos_x), pos_y(pos_y), alto(alto), ancho(ancho), tipo(tipo) {}
    RecogibleDTO(): pos_x(), pos_y(), alto(), ancho(), tipo() {}
} __attribute__((packed));

class SnapshotDTO {
private:
    TipoEscenario tipo_escenario;
    std::vector<BloqueEscenarioDTO> bloques_escenario;
    std::vector<ClienteDTO> clientes;
    std::vector<BalaDTO> balas;
    std::vector<EnemigoDTO> enemigos;
    std::vector<RecogibleDTO> recogibles;
    int tiempo_restante;
    bool fin_juego;

public:
    SnapshotDTO();

    explicit SnapshotDTO(TipoEscenario tipo_escenario);

    SnapshotDTO(std::vector<ClienteDTO> clientes, std::vector<BloqueEscenarioDTO> bloques,
                TipoEscenario tipo_escenario);

    void establecer_tipo_escenario(TipoEscenario tipo_escenario);

    [[nodiscard]] TipoEscenario obtener_tipo_escenario() const;

    void agregar_cliente(ClienteDTO cliente);

    std::vector<ClienteDTO>& obtener_clientes();

    void agregar_bala(BalaDTO bala);

    std::vector<BalaDTO>& obtener_balas();

    void agregar_enemigo(EnemigoDTO enemigo);

    std::vector<EnemigoDTO>& obtener_enemigos();

    void agregar_recogible(RecogibleDTO recogible);

    std::vector<RecogibleDTO>& obtener_recogibles();

    void agregar_bloque_escenario(BloqueEscenarioDTO bloque_escenario);

    std::vector<BloqueEscenarioDTO>& obtener_bloques_escenario();

    void agregar_tiempo_restante(int tiempo);

    [[nodiscard]] int obtener_tiempo_restante() const;

    [[nodiscard]] bool es_fin_juego() const;

    void establecer_fin_juego(bool fin_juego);
};

#endif
