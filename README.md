# Jazz-Jackrabbit
Trabajo Práctico Grupal de la materia Taller de Programación (TA045).

## Integrantes:
* Agustín Altamirano - Padrón 110237
* Santiago Fassio - Padrón 109463
* Federico Genaro - Padrón 109447
* Netanel Jamilis - Padrón 99093 


## Instalación de dependencias
La instalación de dependencias se puede realizar ejecutando los siguientes comandos:

```
git submodule update --init --recursive
sh install.sh
```
Al hacerlo, también se compila el juego.

## Compilación

Si se desea recompilar el juego, se debe ejecutar el siguiente comando:

```
sh build.sh
```

## Ejecución

Para ejecutar el servidor, se debe ejecutar el siguiente comando:

```
./Server <puerto>
```

Para ejecutar el cliente, se debe ejecutar el siguiente comando:

```
./Client <hostname> <puerto>
```

Para ejecutar el editor de mapas, se debe ejecutar el siguiente comando:

```
./editor
```