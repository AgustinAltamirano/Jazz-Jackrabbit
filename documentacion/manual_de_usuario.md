# Manual de usuario

## Introducción
El juego es un remake multijugador del Jazz Jackrabbit 2, un shooter de plataformas de los años 90 producido
por Epic MegaGames.

El juego consiste en partidas de corta duración de dos o más jugadores. El objetivo es obtener la mayor cantidad de
puntos posible, ya sea recolectando gemas, monedas, eliminando enemigos u otros jugadores.

## Requisitos

El juego fue desarrollado para ejecutarse en el sistema operativo Ubuntu 22.04 LTS. Sin embargo, funciona también en
otras distribuciones de Linux basadas en Ubuntu o Debian.

Para la instalación, es necesario tener instalado [git](https://git-scm.com/).

## Instalación

El primer paso es clonar el repositorio. En una terminal, ejecutar los siguientes comandos:

```bash
git clone https://github.com/AgustinAltamirano/Jazz-Jackrabbit.git
git submodule update --init --recursive
```

Una vez realizado esto, se debe ejecutar el siguiente comando, con el cual se instalará y compilará todo el proyecto y
sus dependencias:

```bash
sh install.sh
```

## Ejecución

Para poder jugar, se necesita primero iniciar el servidor. Esto se logra ejecutando el siguiente comando desde una
terminal en el directorio `build`:

```bash
./Server <puerto>
```

donde `<puerto>` es el puerto donde se desea abrir el servidor. Ejemplo: `./Server 8080`.

Luego, cada uno de los jugadores que deseen jugar deben ejecutar el siguiente comando desde una terminal en el
directorio `build`:

```bash
./Client <ip> <puerto>
```

donde `<ip>` es la dirección IP del servidor y `<puerto>` es el puerto donde se encuentra el servidor. Ejemplo:
`./Client 127.0.0.1 8080`.

Una vez finalizada la partida, el jugador puede cerrar el cliente desde la interfaz gráfica. Cuando se desee cerrar el
servidor, se debe ingresar la letra `q` en la terminal donde se está ejecutando.

De forma adicional, se cuenta con un editor de mapas, el cual permite crear mapas personalizados para el juego. Para
ejecutar el editor, se debe ejecutar el siguiente comando desde una terminal en el directorio `build`:

```bash
./editor
```

El editor se puede cerrar desde la interfaz gráfica. Más adelante se explica a detalle su uso.

## Comenzar a jugar

Una vez iniciado el servidor, al unirse un nuevo jugador podrá ver la pantalla de inicio:

![Pantalla de inicio](img/pantalla_inicio.png)

Haciendo click, se abrirá el menú principal del juego:

![Menú principal](img/menu_principal.png)

Allí, se puede seleccionar si se desea crear una nueva partida (_NEW GAME_) o unirse a una ya existente (_JOIN GAME_).

### Crear una partida

Para crear una partida, se debe seleccionar la opción _NEW GAME_ del menú principal.