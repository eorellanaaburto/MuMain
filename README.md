# Fuentes del cliente MU Online (MuMain)

[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/sven-n/MuMain)

Este es mi fork personal de los fuentes del cliente Season 5.2 subidos por
[Luois](https://github.com/LouisEmulator/Main5.2).

El objetivo final es limpiarlo, hacerlo compatible y dejarlo completo para
Season 6 Episodio 3.

## Cambios realizados

* El framerate fue aumentado.
  * Por defecto usa V-Sync sin límite de FPS. Si V-Sync no está disponible,
    limita a 60 FPS.
  * El menú de opciones incluye una casilla para reducir efectos y lograr más FPS.
  * Comandos de chat:
    * Cambiar el límite de FPS: `$fps <valor>`
    * V-Sync: `$vsync on` / `$vsync off`
    * Contador simple de FPS: `$fpscounter on` / `$fpscounter off`
    * Panel de detalles (FPS, cuadros más lentos, gráfico de tiempo por cuadro, build, escena, mouse y cámara): `$details on` / `$details off`
    * Estadísticas de SDL GPU (draw, merge, buffers, texturas y tiempos de CPU por pase, incluyendo skinning, simulación de efectos y present): `$glstats on` / `$glstats off`
* El renderizado usa comandos diferidos de SDL GPU, quads indexados y strips,
  buffers por cuadro que crecen según necesidad y fusión segura de draws adyacentes.
* La serie de rendimiento Core Profile de upstream está mapeada a SDL GPU (ver
  [docs/GPU Skinning/glperf](docs/GPU%20Skinning/glperf/README.md)): paletas de
  huesos 3x4 empaquetadas, estadísticas del renderer, atribución por pase,
  crecimiento de buffers y generación de geometría de sprites sin heap se conservan
  sin restaurar el RHI de OpenGL retirado.
* Se agregaron extensiones de inventario y bóveda.
* El sistema de habilidades maestras fue actualizado a Season 6.
* Soporte Unicode: el cliente trabaja con UTF-16LE en lugar de ANSI en memoria.
  Todas las cadenas y arreglos de caracteres usan caracteres anchos. Las cadenas
  que llegan desde archivos y la red se manejan como UTF-8.
* Se reemplazó el stack de red por MUnique.OpenMU.Network para facilitar los cambios.
  Este repositorio incluye una biblioteca cliente en C# .NET 10 compilada con Native AOT.
* El protocolo de red fue adaptado a Season 6 Episodio 3. Todavía puede quedar
  trabajo pendiente, pero conecta con [OpenMU](https://github.com/MUnique/OpenMU)
  y es jugable. Además, el protocolo fue extendido y ya no es estándar.
  * Daño, experiencia, etc. pueden superar 16 bits.
  * Serialización de ítems mejorada.
  * Serialización de apariencia mejorada.
  * Barra de estado de salud del monstruo después de un ataque.
* Se incorporaron cambios significativos de Qubit, como:
  * Clase Rage Fighter.
  * Corrección visual cuando el Dark Lord camina con el Raven.
  * Equipar ítems con clic derecho.
  * Brillo para Fenrir rojo, azul y negro.
  * Resoluciones de pantalla adicionales.
* Se incorporó la interfaz y la lógica de MU Helper. Hay trabajo pendiente, pero la
  funcionalidad principal es utilizable.
* Sistema de reconexión automática.
* Se eliminaron los if-defs de la clase Rage Fighter, ya que el objetivo es
  Season 6; Rage Fighter siempre se incluye.
* Algunas correcciones menores, por ejemplo:
  * Etiquetas de los ítems Storm Crow.
  * Etiquetas de los sets Ancient.
* El código fue refactorizado. Muchos valores mágicos fueron reemplazados por
  enums y constantes.
* Nuevo sistema de traducción (ver [docs/translation-system.md](docs/translation-system.md)).

## Cambios recientes en este fork (servidor OpenMU Season 8)

Estos cambios apuntan al servidor OpenMU S8 del proyecto. Algunos aún no están
verificados en juego, como el bono de pentagrama (requiere desplegar el servidor con el paquete de 21 bytes).

* **Habilidades maestras (maestría):** se corrigió el lanzamiento y las animaciones
  de las maestrías de todas las clases. Los identificadores de maestría se mapean a
  su habilidad base y se agregaron las definiciones de maestría faltantes (por ejemplo
  Deathstab, Strike of Destruction, Blood Storm, Multi-Shot, Poison Arrow, Blind,
  Dragon Roar y Dragon Slasher). Electric Spark usa la misma ruta que Thunder Strike.
* **NPC Adniel (582, Maestro de Elementos):**
  * Al hablar con Adniel, el servidor envía el estado del pentagrama equipado y el
    cliente lo muestra en el registro del sistema: nivel del pentagrama y rango y
    nivel de cada Errtel (Anger, Blessing, Integrity, Divinity, Gale).
  * El menú de Adniel tiene la opción de crear Mithril, Elixir y Errtel. Antes
    esto se hacía solo con el chat `/ecraft`; ahora el menú envía ese mismo comando
    al servidor. Tasas de la guía: Mithril 80%, Elixir 60% y Errtel 50%, con un costo de
    100.000 Zen cada una.
  * Cerrar el menú de Adniel cierra también el diálogo del NPC.
* **Bonos del pentagrama:** al pasar el mouse sobre el pentagrama en el slot Artifact,
  el tooltip lista el bono elemental de cada Errtel activo según su nivel. El
  servidor envía el número de opción de cada Errtel en el paquete de estado de Adniel
  (paquete `C3 30 2A` de 21 bytes). Si el servidor es anterior, el tooltip muestra
  solo el nombre del pentagrama.
* **Ítems de crafteo:** Mithril (12/145) y Elixir (12/147) están definidos en
  `Data/Items/Group12_Wing.json`.
* **Límite de personajes:** la lista de personajes soporta 6 por cuenta, usando el
  paquete extendido de lista de personajes (C2).
* **Divinity y Gale** dejaron de mostrarse en el menú de Adniel; sus botones no se usaban.

## Cómo compilar y ejecutar

### Requisitos

* **CMake** 3.25 o superior (incluido con Visual Studio y CLion).
* **.NET SDK 10.0** o superior (para compilar la biblioteca cliente).
* **Visual Studio 2022+** con las cargas de trabajo de C++ y C#, **CLion** o **Rider**
  (ver las instrucciones específicas de cada IDE más abajo).
* Un servidor compatible: [OpenMU](https://github.com/MUnique/OpenMU).

### Primera vez: inicializar los submódulos

El proyecto usa tres submódulos de git bajo `src/ThirdParty/`:

* `SDL`: backend de ventana, entrada y audio (necesario para todas las compilaciones).
* `SDL_mixer`: mezclador de audio (necesario para todas las compilaciones).
* `imgui`: interfaz del editor dentro del juego (solo si se compila con `-DENABLE_EDITOR=ON`,
  independiente de Debug/Release).

CMake inicializa estos submódulos automáticamente en la primera configuración. Si
falla por cualquier motivo, ejecuta desde la raíz del repositorio:

```bash
git submodule update --init
```

### Configuraciones de compilación

Hay dos opciones independientes: **editor encendido o apagado** (al configurar, con un
preset) y **Debug/Release** (al compilar).

#### Compilaciones con editor (`windows-x86-mueditor` / `windows-x64-mueditor`)

* El preset de configuración define `ENABLE_EDITOR=ON`.
* Incluye el editor MU dentro del juego (basado en ImGui); el submódulo `imgui` debe estar inicializado.
* Presiona **F12** dentro del juego para mostrar u ocultar el editor.
* Inicia con el parámetro `--editor` para abrirlo habilitado.
* Definición del preprocesador: `_EDITOR`.

#### Compilaciones estándar (`windows-x86` / `windows-x64`)

* El preset de configuración define `ENABLE_EDITOR=OFF`; no se compila código del
  editor y el submódulo `imgui` no se inicializa.
* Sin sobrecarga de editor.

Cualquiera de las dos configuraciones puede compilarse como Debug o Release con el
preset de compilación correspondiente (`*-debug` o `*-release`).

### Compilar con CMake y MinGW-w64 (Linux)

El repositorio también incluye una configuración de CMake para compilar de forma cruzada
el cliente para Windows desde Linux usando un toolchain MinGW-w64.

**Requisitos previos**

* Un toolchain MinGW-w64 funcional (por ejemplo `i686-w64-mingw32-g++`).
* Una compilación MinGW-w64 de libjpeg-turbo que provea la biblioteca `libturbojpeg`
  (estática o de importación) en la ruta de búsqueda de bibliotecas del toolchain.
* Las bibliotecas estándar de Windows / OpenGL incluidas con MinGW-w64 (por ejemplo
  `opengl32`, `glu32`, `winmm`, `imm32`, `ws2_32`, etc.).

**Ejemplo de comandos en Linux**

Desde la raíz del repositorio:

```sh
cmake -S . -B build-mingw \
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-i686.cmake \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build-mingw -j$(nproc)
```

Si el enlazador informa `cannot find -lturbojpeg`, instala una compilación MinGW-w64
de libjpeg-turbo (que provea `libturbojpeg.a` / `libturbojpeg.dll.a`) o ajusta la
entrada `target_link_libraries` en `src/CMakeLists.txt` al nombre de la biblioteca
disponible en tu sistema.

---

### Compilar el proyecto

El proyecto usa **CMake** como sistema de compilación. La biblioteca `.NET Client Library`
la compila CMake automáticamente al compilar el proyecto principal; no hace falta publicarla a mano.

#### Opción 1: Visual Studio 2022+ (recomendada)

1. **Abrir el proyecto:**
   * Archivo → Abrir → Carpeta.
   * Selecciona la carpeta raíz `MuMain` (no `src`).

2. **Esperar a que CMake configure** (ocurre automáticamente; revisa la ventana Salida).

3. **Seleccionar la configuración de compilación:**
   * Usa el desplegable para elegir `x86-Debug` o `x86-Release`.

4. **Compilar:**
   * Compilar → Compilar todo, o presiona `Ctrl+Shift+B`.

5. **Ejecutar / depurar:**
   * Selecciona `Main.exe` como elemento de inicio.
   * Presiona `F5` para depurar o `Ctrl+F5` para ejecutar sin depurador.
   * El directorio de trabajo se configura automáticamente en `src/bin`.

**Nota:** El directorio de trabajo está preconfigurado en `.vs/launch.vs.json`. Si no
funciona, asegúrate de haber abierto la carpeta raíz `MuMain`, no una subcarpeta.

#### Opción 2: CLion

1. **Abrir el proyecto:**
   * Archivo → Abrir.
   * Selecciona la carpeta raíz `MuMain`.

2. **Esperar a que CMake configure** (ocurre automáticamente).

3. **Configurar el directorio de trabajo:**
   * Ejecutar → Editar configuraciones.
   * Selecciona `Main`.
   * Define "Working directory" como el directorio de salida de compilación (por ejemplo `cmake-build-debug/src/Debug`).
   * El paso posterior a la compilación copia automáticamente todos los recursos del juego.

4. **Compilar y ejecutar:**
   * Haz clic en el martillo para compilar.
   * Haz clic en el botón de play para ejecutar.

#### Opción 3: Rider (CMake por línea de comandos + Rider para desarrollar)

Rider no tiene soporte completo de CMake para proyectos C++, así que primero hay que generar una solución de Visual Studio:

1. **Generar la solución** (configuración de una sola vez):
   ```bash
   cmake -B build -G "Visual Studio 17 2022" -A Win32
   ```
   *(Ajusta la versión del generador según tu Visual Studio instalado.)*

2. **Abrir en Rider:**
   * Archivo → Abrir.
   * Selecciona `build/MuMain.sln`.

3. **Compilar y ejecutar:**
   * Compilar → Compilar solución.
   * Ejecutar → Ejecutar 'Main'.

**Importante:** Si modificas `CMakeLists.txt`, debes regenerar la solución manualmente ejecutando otra vez el comando de CMake.

#### Opción 4: Compilación por línea de comandos (Windows)

Usando CMakePresets.json con Ninja (igual que los IDE, mucho más rápido que MSBuild):

```powershell
# Configurar la compilación x86 (solo la primera vez, o cuando cambie CMakeLists.txt)
cmake --preset windows-x86

# Compilar Debug
cmake --build --preset windows-x86-debug

# Compilar Release
cmake --build --preset windows-x86-release

# Para compilaciones x64, usa los presets windows-x64
cmake --preset windows-x64
cmake --build --preset windows-x64-debug
```

**Nota:** Ninja Multi-Config permite cambiar entre Debug y Release sin volver a configurar.
Los recursos se copian automáticamente al directorio de salida durante la compilación.

**Para empezar desde cero (compilación limpia):**
```powershell
Remove-Item -Recurse -Force out
```

**Ejecutar el ejecutable:**
```powershell
# x86 Debug
./out/build/windows-x86/src/Debug/Main.exe

# x86 Release
./out/build/windows-x86/src/Release/Main.exe
```

#### Opción 5: Compilación por línea de comandos (Linux) — !Aún no funciona!

Para compilar en Linux hace falta agregar presets de Linux a CMakePresets.json. Flujo de ejemplo:

```bash
# Configurar Debug con Ninja (recomendado)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_EDITOR=OFF

# Compilar
cmake --build build

# Para cambiar a Release, vuelve a configurar:
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_EDITOR=OFF
cmake --build build
```

**Para empezar desde cero (compilación limpia):**
```bash
rm -rf build
```

**Ejecutar el ejecutable:**
```bash
./build/src/Main
```

---

### Ejecutar el cliente

Admite los parámetros de inicio `/u` y `/p`, por ejemplo: `main.exe connect /u192.168.0.20 /p55902`.
También funciona el [lanzador de OpenMU](https://github.com/MUnique/OpenMU/releases/download/v0.8.17/MUnique.OpenMU.ClientLauncher_0.8.17.zip).
Por defecto conecta a localhost en el puerto `44406`.
El cliente se identifica con la versión `2.04d` y el serial `k1Pk2jcET48mxL3b`.

#### Configuración del cliente (`config.ini`)

El cliente lee las opciones desde `config.ini` en el directorio del ejecutable:

| Sección | Clave | Valor por defecto | Descripción |
| :--- | :--- | :--- | :--- |
| **`[UI]`** | `EnableAnimationTaskPool` | `0` | Pon `1` para procesar la animación de personajes con `AnimationTaskPool` cuando haya al menos 20 personajes activos visibles. `0` mantiene las actualizaciones secuenciales. |
| **`[UI]`** | `Locale` | `"en"` | Locale de la interfaz generada que está activo. La ventana de opciones guarda aquí los cambios de idioma en tiempo de ejecución. |
| **`[Camera]`** | `Zoom` | `1735` | Distancia de la cámara orbital guardada entre sesiones. |
| **`[Render]`** | `VSync` | `1` | `1` activa la presentación sincronizada con la pantalla; `0` mantiene V-Sync desactivado entre reinicios y cambios de pantalla completa o resolución. `$vsync on` / `$vsync off` actualizan este valor. |

El renderizado siempre usa el backend SDL GPU. La clave heredada `[Render] CoreProfile`
no se lee; los valores `0` y `1` no tienen efecto y no seleccionan un contexto de OpenGL.

#### Parámetros de línea de comandos y opciones

* **Cadena de conexión:** `main.exe connect /u<IP> /p<PUERTO>`.
* **`--enable-taskpool`:** activa `AnimationTaskPool` sin importar `config.ini`; el
  umbral de 20 personajes sigue aplicando.
* **`--editor`:** inicia el editor ImGui habilitado en las compilaciones `*_mueditor`;
  **F12** lo muestra u oculta.

## Documentación

* [Renderizado con GPU skinning y SDL GPU](docs/GPU%20Skinning/README.md): el mapeo
  hacia abajo para el trabajo de Core Profile, GPU skinning y DXP de upstream.
* [Sistema de cámara](docs/camera-system.md): modos, cambio de modo (F9), configuración,
  culling por frustum, panel `$details` y los cambios de comportamiento de juego
  producidos por la reforma de la cámara 3D.
* [Ventana de comandos de chat](docs/chat-commands.md): los comandos que ofrece el
  servidor (J), cómo se ingresan sus valores y cómo se guardan favoritos y plantillas.
* [DevEditor](docs/dev-editor.md): la interfaz de ajuste dentro del juego (F12, solo
  compilaciones de depuración), incluida la [pestaña Map Editor](docs/dev-editor.md#33-map-editor-tab)
  para texturas, altura y atributos del terreno, objetos del mundo y captura del minimapa.
* [Ventana de opciones y configuración](docs/options-window.md): cambio de resolución
  y ventana/pantalla completa en tiempo de ejecución, redondeo de deslizadores y lo que
  la ventana de opciones guarda en `config.ini`.
* [Guía de compilación](docs/build/README.md): notas de compilación por plataforma.
* [Pruebas dentro del juego](docs/in-game-tests.md): el probador junto a las compilaciones
  de desarrollo, que ejecuta escenarios con clientes reales contra un servidor de pruebas
  OpenMU nuevo y genera un reporte con una captura por paso.
* [Socket de control](docs/control-socket.md): el socket de desarrollo por el que los
  scripts y las pruebas dentro del juego controlan el cliente.
* [Sistema de traducción](docs/translation-system.md): cómo funciona el flujo de .resx a
  accesores C++ generados, cómo agregar una cadena o un locale, el cambio de locale en
  tiempo de ejecución y los observadores para cadenas de UI en caché.

## Contribuir

### Reglas de código

Todos los cambios de código, hechos por personas o por asistentes de IA, deben seguir
[`docs/CODING_RULES.md`](docs/CODING_RULES.md). Léelas antes de abrir un PR.

Los asistentes de código con IA (Claude Code, Cursor, Codex, etc.) también deben leer
[`AGENTS.md`](AGENTS.md), que apunta a las mismas reglas y a la guía de compilación.

## Créditos

* Webzen
* Louis
* Qubit (tuservermu.com.ve)
* Miembros de la comunidad de RaGEZONE y tuservermu.com.ve por publicar correcciones
* [Nitoy](https://github.com/nitoygo) por MU Helper
