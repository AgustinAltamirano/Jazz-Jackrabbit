# Organizacion Semanal

A lo largo del desarrollo del proyecto, establecimos objetivos de forma semanal con el fin de subdividir todos los
requerimientos del enunciado.

### Semana 0

* Instalación del entorno de desarrollo, librerías y herramientas necesarias. Planteo inicial de estructura del proyecto
  y requisitos básicos.
* Creación de tablero de tareas y canales de comunicación

### Semana 1

* Creación del archivo de configuración **YAML**
* Implementación de las clases `ObjetoAnimado`, `LectorTexturas` y `AdministradorVistaJuego`
* Pruebas de concepto de vista con **SDL** y **QT**
* Creación prototipo de comunicación cliente servidor

### Semana 2

* Implementación de la clase `personaje`
* Implementación de la física de **colisiones** del jugador
* Implementación de las clases `Jugador` y `EntradaJuego`. Actualización de la prueba de concepto de la vista de juego.
* Diseño paquetes e implementación de clases de comunicación del cliente con la vista del juego y el menú.
* Implementación de la clase `VentanaInicial` y `MenuPrincipal`.

### Semana 3

* Implementación del salto y movimiento básico del personaje
* Implementación del cambio de arma del personaje
* Implementación de la lógica de los estados del personaje
* Implementación de la gestión de partidas en el servidor
* Refactorización de `AdministradorVistaJuego` para actualizar y sincronizar la vista
* Implementación de las clases `FondoEscenario`, `BloqueEscenario` y `Camara`
* Creación del **gestor de partidas**
* Implementación de la clase `MenuCrearPartida`, `MenuSeleccion`, `MenuSeleccionMapa` y `MenuSeleccionJugador`.
* Implementación de la clase `BotonMenu`.

### Semana 4

* Implementación de las `balas` y sus físicas con el entorno
* Implementación de los objetos `recogibles` en el entorno
* Implementación de `enemigos` y sus físicas de colisiones
* implementación de la lectura de archivos de mapas
* Implementación del protocolo para el envío de snapshots
* **POC unit tests**
* Implementación del **HUD** y la pantalla de carga del juego
* Corrección de errores de `ObjetoAnimado` y `AdministradorVistaJuego`
* Implementación de la clase `ManejadorSprites`, `SpritesJugador` y `SpritesMapa`, usándolas en las clases creadas
  anteriormente.
* Implementación de la clase `BotonAnimado`, `BotonAnimadoMapa` y `BotonAnimadoJugador`, para poder usarlas en los
  manejadores de sprites correspondientes.
* Implementación de las clases para el Editor de mapas (`BarraMenu`, `EscenaEditor`, `ListaBotones` y `MainWindow`), con
  la funcionalidad para poder crear los mapas con los bloques correspondientes a cada tipo de escenario, borrar los
  bloques, y cambiar de escenario (y que se actualicen las texturas de los bloques ya colocados).

### Semana 5

* Arreglo del salto del personaje, implementación del salto en movimiento
* Arreglo del cálculo de colisiones
* Implementación del **tiempo** en gameloop y de la duración determinada de una partida
* Correcciones CR gestión de partidas y protocolo
* Integración y conexión de todas las partes del proyecto
* Creación de **scripts** de instalación y compilación
* Implementación de las clases `AdminEnemigos`, `AdminBalas` y `AdminRecogibles`
* Cargadas texturas restantes y texturas de tipografía
* Corrección de errores de animación en la vista del juego
* Implementación de funcionalidad de **"Guardar"**, **"Guardar como"** y **"Cargar"** para el Editor de mapas.
* Implementación de funcionalidad de las barras de desplazamiento en el mapa, para poder crear mapas con una mayor
  dimensión al viewport mostrado.
* Agregado de chequeos al unirse a una partida (con un popup informando en caso de fallo).
* Agregado de chequeos al ingresar el nombre de un mapa personalizado creado con el Editor de mapas (se chequea que
  exista dicho mapa y, en caso de no existir, se muestra un popup informando).

### Semana 6

* Implementación de que los enemigos dejan caer objetos al morir
* Implementación del **dash** (correr muy rápido)
* Implementación del **ataque especial**
* Implementación de la lógica de los bloques rampa
* Implementación de los **trucos**
* Actualización del HUD para mostrar el top de jugadores, el número de jugador y el tiempo restante
* Implementación de la **pantalla de fin de juego**, actualización de la pantalla de carga y cambios en el procesamiento
  de la entrada de juego.
* Correcciones de errores visuales de la vista de juego
* Implementación de las clases `ReproductorMusica`, `ReproductorSonidos` y `AdminSonidos`
* Actualización de la snapshot para comunicar los eventos de **sonido** producidos
* Implementada clase `AdminExplosiones`
* Ajustes y solución de problemas del servidor y protocolo
* **Tests unitarios** de protocolo
* **Documentación** del proyecto
* Correcciones en el guardado de los mapas del Editor.
* Agregado de comportamiento al cerrar el menú anticipadamente (sin terminar de seleccionar todas las opciones).

# División de tareas

El proyecto fue dividido en cuatro categorías:

* Vista del menú y editor de mapas con QT
* Vista y animaciones del juego con SDL y SDL2pp
* Arquitectura cliente-servidor, comunicación y protocolo
* Lógica de juego y físicas

El alumno responsable en llevar a cabo la lógica de QT, menús y el editor de mapas fue Federico Genaro. En particular se
encargó de:

* Implementación del menú principal con QT, la cual incluye la ventana para crear nuevas partidas y la ventana para
  unirse a partidas ya creadas, junto con la selección del jugador y de los mapas (con popups y animaciones).
* Implementación del editor de partidas con QT, el cual permite la creación de mapas personalizados e incluye las
  opciones para guardar un mapa y cargar uno ya creado a partir de un archivo YAML.

El alumno responsable en llevar a cabo implementación de la vista y animaciones con SDL fue Agustín Altamirano. Entre
sus tareas se encontraron:

* Modelación de clases para los elementos y entidades visuales del juego, haciendo uso de las funcionalidades de SDL2 y
  SDL2pp.
* Diseño e implementación de sistema de carga de texturas y sprites del juego.
* Implementación de un sistema de actualización y renderizado de la vista, manteniendo siempre una sincronización
  constante.
* Modelación de clases para reproducir música y efectos de sonido dentro del juego.

El alumno responsable en llevar a cabo la arquitectura cliente-servidor fue Netanel Jamilis. En particular se encargó
de:

* Implementar protocolo de comunicación cliente - servidor
* Implementar interfaces de comunicación de la vista (SDL + QT) con el cliente del sistema
* Implementar manejo de partidas
* Crear units tests del protocolo

El alumno responsable en llevar a cabo la lógica de juego y físicas de las entidades fue Santiago Fassio. En particular
se encargó de:

* Implementar el movimiento de los jugadores y otras entidades en el entorno de juego
* Implementar la física de colisiones de los jugadores y otras entidades con los bloques del juego.
* Implementar la física de la gravedad sobre los jugadores.
* Implementar el procesamiento de las acciones, estados y gravedad de los jugadores y otras entidades del juego.
* Implementar lógica de jugabilidad, diferentes comportamientos de los enemigos, jugadores y armas.

# Herramientas utilizadas

* Librerías gráficas QT, SDL2 (Simple DirectMedia Layer versión 2) y SDL2pp
* Entorno de desarrollo CLion
* Librería de testing Acutest
* Formateadores y linters de código cppcheck, clang-format y cpplint
* Trello para la división de tareas

# Documentación utilizada acerca de las herramientas mencionadas

* SDL2: [SDL2](https://www.libsdl.org/)
* SDL2pp: [SDL2pp](https://github.com/libSDL2pp/libSDL2pp) (se consultó un tutorial de SDL2pp, disponible
  en [tutorial SDL2pp](https://github.com/libSDL2pp/libSDL2pp-tutorial))
* Acutest: [Acutest](https://github.com/mity/acutest)
* QT: [QT](https://doc.qt.io/)

# Errores conocidos

* Al saltar en la dirección de una pared vertical el jugador se puede quedar atascado en el aire a menos que el jugador
  se mueva en la dirección opuesta a la pared.
* El jugador no puede saltar en rampas.
* El menú de selección de mapas pierde el foco cuando usamos el teclado y nos "salimos" o pasamos de la opción superior
  o inferior de la lista de botones.

# Puntos problemáticos

* Cómo procesar la posición de un jugador sobre una rampa.
* La carga de coordenadas de texturas con el método utilizado resultó bastante tediosa.
* Resultó desafiante la implementación del protocolo de tal forma que contemple el endianness del cliente y del servidor
  para cada uno de los datos de la snapshot de juego, manteniéndose a su vez lo más sencillo posible.

# Features faltantes

Si bien llegamos a implementar todas las características requeridas por el enunciado del trabajo, existen un par de
cosas que nos hubiera gustado implementar de forma adicional, pero que no pudimos hacerlo:

* Sistema para leer las teclas usadas para cada acción de juego desde un archivo de configuración
* Animación para algunos objetos recogibles

# Si volviéramos a hacer el proyecto ¿Qué cambiaríamos?

Consideramos que hubiera sido preferible organizarnos para realizar la integración de cada una de las partes del
proyecto con mayor antelación, para así disponer de más tiempo para testear el funcionamiento en su totalidad e
implementar nuevas features sobre esa base. También hubiese estado bueno incorporar los unit tests en una etapa más
temprana del proyecto para prevenir errores y ahorrar tiempo de debugging.
