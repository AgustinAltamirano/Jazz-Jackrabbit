#ifndef GAME_SNAPSHOTDTO_H
#define GAME_SNAPSHOTDTO_H

#include <cstdint>
#include <vector>

#include <arpa/inet.h>

#include "estado_personaje.h"
#include "tipo_arma.h"
#include "tipo_bloque_escenario.h"
#include "tipo_enemigo.h"
#include "tipo_escenario.h"
#include "tipo_personaje.h"
#include "tipo_recogible.h"

struct ClienteDTO {
private:
    int32_t id_cliente, pos_x, pos_y;
    uint32_t vida, puntos;
    int32_t balas_restantes;
    TipoPersonaje tipo_personaje;
    bool de_espaldas;
    EstadoPersonaje estado;
    TipoArma arma_actual;

public:
    ClienteDTO(const int32_t id_cliente, const TipoPersonaje tipo_personaje, const int32_t pos_x,
               const int32_t pos_y, const bool de_espaldas, const EstadoPersonaje estado,
               const uint32_t vida, const uint32_t puntos, const TipoArma arma_actual,
               const int32_t balas_restantes):
            id_cliente(htonl(id_cliente)),
            pos_x(htonl(pos_x)),
            pos_y(htonl(pos_y)),
            vida(htonl(vida)),
            puntos(htonl(puntos)),
            balas_restantes(htonl(balas_restantes)),
            tipo_personaje(tipo_personaje),
            de_espaldas(de_espaldas),
            estado(estado),
            arma_actual(arma_actual) {}
    ClienteDTO():
            id_cliente(),
            pos_x(),
            pos_y(),
            vida(),
            puntos(),
            balas_restantes(),
            tipo_personaje(),
            de_espaldas(),
            estado(),
            arma_actual() {}

    [[nodiscard]] int32_t obtener_id_cliente() const { return ntohl(id_cliente); }

    [[nodiscard]] TipoPersonaje obtener_tipo_personaje() const { return tipo_personaje; }

    [[nodiscard]] int32_t obtener_pos_x() const { return ntohl(pos_x); }

    [[nodiscard]] int32_t obtener_pos_y() const { return ntohl(pos_y); }

    [[nodiscard]] bool obtener_de_espaldas() const { return de_espaldas; }

    [[nodiscard]] EstadoPersonaje obtener_estado() const { return estado; }

    [[nodiscard]] uint32_t obtener_vida() const { return ntohl(vida); }

    [[nodiscard]] uint32_t obtener_puntos() const { return ntohl(puntos); }

    [[nodiscard]] TipoArma obtener_arma_actual() const { return arma_actual; }

    [[nodiscard]] int32_t obtener_balas_restantes() const { return ntohl(balas_restantes); }

} __attribute__((packed));

struct BloqueEscenarioDTO {
private:
    int32_t pos_x, pos_y, angulo;
    uint32_t ancho, alto;
    TipoBloqueEscenario tipo;

public:
    BloqueEscenarioDTO(const int32_t pos_x, const int32_t pos_y, const uint32_t ancho,
                       const uint32_t alto, const int32_t angulo, const TipoBloqueEscenario tipo):
            pos_x(htonl(pos_x)),
            pos_y(htonl(pos_y)),
            angulo(htonl(angulo)),
            ancho(htonl(ancho)),
            alto(htonl(alto)),
            tipo(tipo) {}

    BloqueEscenarioDTO(): pos_x(), pos_y(), angulo(), ancho(), alto(), tipo() {}

    [[nodiscard]] int32_t obtener_pos_x() const { return ntohl(pos_x); }

    [[nodiscard]] int32_t obtener_pos_y() const { return ntohl(pos_y); }

    [[nodiscard]] uint32_t obtener_ancho() const { return ntohl(ancho); }

    [[nodiscard]] uint32_t obtener_alto() const { return ntohl(alto); }

    [[nodiscard]] int32_t obtener_angulo() const { return ntohl(angulo); }

    [[nodiscard]] TipoBloqueEscenario obtener_tipo() const { return tipo; }

} __attribute__((packed));

struct BalaDTO {
private:
    int32_t pos_x, pos_y;
    TipoArma tipo;
    bool choco;

public:
    BalaDTO(const int32_t pos_x, const int32_t pos_y, const TipoArma tipo, const bool choco):
            pos_x(htonl(pos_x)), pos_y(htonl(pos_y)), tipo(tipo), choco(choco) {}

    BalaDTO(): pos_x(), pos_y(), tipo(), choco(false) {}

    [[nodiscard]] int32_t obtener_pos_x() const { return ntohl(pos_x); }

    [[nodiscard]] int32_t obtener_pos_y() const { return ntohl(pos_y); }

    [[nodiscard]] TipoArma obtener_tipo() const { return tipo; }

    [[nodiscard]] bool obtener_choco() const { return choco; }
} __attribute__((packed));

struct EnemigoDTO {
private:
    int32_t id, pos_x, pos_y, alto, ancho;
    TipoEnemigo tipo;
    bool invertido;

public:
    EnemigoDTO(const int32_t id, const int32_t pos_x, const int32_t pos_y, const int32_t alto,
               const int32_t ancho, const TipoEnemigo tipo, const bool invertido):
            id(htonl(id)),
            pos_x(htonl(pos_x)),
            pos_y(htonl(pos_y)),
            alto(htonl(alto)),
            ancho(htonl(ancho)),
            tipo(tipo),
            invertido(invertido) {}

    EnemigoDTO(): id(), pos_x(), pos_y(), alto(), ancho(), tipo(), invertido() {}

    [[nodiscard]] int32_t obtener_id() const { return ntohl(id); }

    [[nodiscard]] int32_t obtener_pos_x() const { return ntohl(pos_x); }

    [[nodiscard]] int32_t obtener_pos_y() const { return ntohl(pos_y); }

    [[nodiscard]] int32_t obtener_alto() const { return ntohl(alto); }

    [[nodiscard]] int32_t obtener_ancho() const { return ntohl(ancho); }

    [[nodiscard]] TipoEnemigo obtener_tipo() const { return tipo; }

    [[nodiscard]] bool obtener_invertido() const { return invertido; }

} __attribute__((packed));

struct RecogibleDTO {
private:
    int32_t pos_x, pos_y, alto, ancho;
    TipoRecogible tipo;

public:
    RecogibleDTO(const int32_t pos_x, const int32_t pos_y, const int32_t alto, const int32_t ancho,
                 const TipoRecogible tipo):
            pos_x(htonl(pos_x)),
            pos_y(htonl(pos_y)),
            alto(htonl(alto)),
            ancho(htonl(ancho)),
            tipo(tipo) {}

    RecogibleDTO(): pos_x(), pos_y(), alto(), ancho(), tipo() {}

    [[nodiscard]] int32_t obtener_pos_x() const { return ntohl(pos_x); }

    [[nodiscard]] int32_t obtener_pos_y() const { return ntohl(pos_y); }

    [[nodiscard]] int32_t obtener_alto() const { return ntohl(alto); }

    [[nodiscard]] int32_t obtener_ancho() const { return ntohl(ancho); }

    [[nodiscard]] TipoRecogible obtener_tipo() const { return tipo; }
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
    bool hubo_disparo;
    bool alguien_fue_herido;
    bool alguien_murio;

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

    void establecer_hubo_disparo(bool disparo);

    void establecer_hubo_herido(bool herido);

    void establecer_hubo_muerte(bool muerte);

    [[nodiscard]] bool obtener_hubo_disparo() const;

    [[nodiscard]] bool obtener_hubo_herido() const;

    [[nodiscard]] bool obtener_hubo_muerte() const;
};

#endif
