# Jazz-Jackrabbit
Trabajo Práctico Grupal de la materia Taller de Programación (TA045).

## Integrantes:
* Agustín Altamirano - Padrón 110237
* Santiago Fassio - Padrón 109463
* Federico Genaro - Padrón 109447
* Netanel Jamilis - Padrón 99093 


## Instalación de dependencias
La instalación de dependencias se puede realizar ejecutando los siguientes comandos:

```bash
git submodule update --init --recursive
sh install.sh
```
Al hacerlo, también se compila el juego.

## Compilación

Si se desea recompilar el juego, se debe ejecutar el siguiente comando:

```bash
sh build.sh
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

## Ejecución de tests

Para ejecutar los tests de protocolo, se debe ejecutar el siguiente comando:

```bash
sh run_protocol_tests.sh
```