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

## Tabla de maestrías

Árbol de maestrías del servidor (Season 6 / OpenMU) por clase. Cada fila es una
maestría con su raíz (rama del árbol), su rango (nivel dentro de la rama), su nivel
máximo y la maestría que debe estar aprendida antes.

Fuente: definiciones de `Persistence/Initialization/VersionSeasonSix/SkillsInitializer.cs`
del servidor OpenMU, 172 maestrías. Si la base de datos del servidor tiene valores
distintos, prevalece la base de datos.

| Clase | Raíz | Rango | Maestría | Nivel máx. | Requisito |
| :--- | :--- | :---: | :--- | :---: | :--- |
| Todas (excepto Fist Master) | Izquierda (común) | 1 | Durability Reduction (1) | 20 | — |
| Todas (excepto Fist Master) | Izquierda (común) | 1 | PvP Defence Rate Inc | 20 | — |
| Todas (excepto Fist Master) | Izquierda (común) | 2 | Automatic Mana Rec Inc | 20 | — |
| Todas (excepto Fist Master) | Izquierda (común) | 2 | Ice Resistance Increase | 20 | Lightning Resistance Inc |
| Todas (excepto Fist Master) | Izquierda (común) | 2 | Lightning Resistance Inc | 20 | Poison Resistance Inc |
| Todas (excepto Fist Master) | Izquierda (común) | 2 | Maximum SD increase | 20 | — |
| Todas (excepto Fist Master) | Izquierda (común) | 2 | Poison Resistance Inc | 20 | — |
| Todas (excepto Fist Master) | Izquierda (común) | 3 | Automatic HP Rec Inc | 20 | Automatic Mana Rec Inc |
| Todas (excepto Fist Master) | Izquierda (común) | 3 | Durability Reduction (2) | 20 | Durability Reduction (1) |
| Todas (excepto Fist Master) | Izquierda (común) | 3 | SD Recovery Speed Inc | 20 | Maximum SD increase |
| Todas (excepto Fist Master) | Izquierda (común) | 4 | Automatic AG Rec Inc | 20 | Automatic HP Rec Inc |
| Todas (excepto Fist Master) | Izquierda (común) | 4 | Defense Increase | 20 | — |
| Todas (excepto Fist Master) | Izquierda (común) | 5 | Defense Success Rate Inc | 20 | Defense Increase |
| Todas (excepto Fist Master) | Izquierda (común) | 5 | Durability Reduction (3) | 20 | Durability Reduction (2) |
| Blade Master | Central | 1 | Attack Succ Rate Inc | 20 | — |
| Blade Master | Central | 2 | Cyclone Strengthener | 20 | Cyclone |
| Blade Master | Central | 2 | Falling Slash Streng | 20 | Falling Slash |
| Blade Master | Central | 2 | Lunge Strengthener | 20 | Lunge |
| Blade Master | Central | 2 | Slash Strengthener | 20 | Slash |
| Blade Master | Central | 3 | Rageful Blow Streng | 20 | Rageful Blow |
| Blade Master | Central | 3 | Twisting Slash Streng | 20 | Twisting Slash |
| Blade Master | Central | 4 | Maximum Life Increase | 20 | — |
| Blade Master | Central | 4 | Rageful Blow Mastery | 20 | Rageful Blow Streng |
| Blade Master | Central | 4 | Twisting Slash Mastery | 20 | Twisting Slash Streng |
| Blade Master | Central | 4 | Weapon Mastery | 20 | — |
| Blade Master | Central | 5 | Death Stab Strengthener | 20 | Death Stab |
| Blade Master | Central | 5 | Maximum Mana Increase | 20 | Maximum Life Increase |
| Blade Master | Central | 5 | Strike of Destr Str | 20 | Strike of Destruction |
| Blade Master | Derecha | 1 | PvP Attack Rate | 20 | — |
| Blade Master | Derecha | 2 | Mace Strengthener | 20 | — |
| Blade Master | Derecha | 2 | One-handed Sword Stren | 20 | — |
| Blade Master | Derecha | 2 | Spear Strengthener | 20 | — |
| Blade Master | Derecha | 2 | Two-handed Sword Stren | 20 | — |
| Blade Master | Derecha | 3 | Mace Mastery | 20 | Mace Strengthener |
| Blade Master | Derecha | 3 | One-handed Sword Mast | 10 | One-handed Sword Stren |
| Blade Master | Derecha | 3 | Spear Mastery | 20 | Spear Strengthener |
| Blade Master | Derecha | 3 | Two-handed Sword Mast | 20 | Two-handed Sword Stren |
| Blade Master | Derecha | 4 | Mana Reduction | 20 | — |
| Blade Master | Derecha | 4 | Monster Attack Life Inc | 20 | — |
| Blade Master | Derecha | 4 | Monster Attack SD Inc | 20 | — |
| Blade Master | Derecha | 4 | Swell Life Strengt | 20 | Swell Life |
| Blade Master | Derecha | 5 | Minimum Attack Power Inc | 20 | — |
| Blade Master | Derecha | 5 | Monster Attack Mana Inc | 20 | Monster Attack Life Inc |
| Blade Master | Derecha | 5 | Swell Life Proficiency | 20 | Swell Life Strengt |
| Grand Master | Central | 2 | Expansion of Wiz Streng | 20 | Expansion of Wizardry |
| Grand Master | Central | 2 | Flame Strengthener | 20 | Flame |
| Grand Master | Central | 2 | Lightning Strengthener | 20 | Lightning |
| Grand Master | Central | 3 | Blast Strengthener | 20 | Cometfall / Lightning Strengthener |
| Grand Master | Central | 3 | Expansion of Wiz Mas | 20 | Expansion of Wiz Streng |
| Grand Master | Central | 3 | Inferno Strengthener | 20 | Inferno / Flame Strengthener |
| Grand Master | Central | 3 | Poison Strengthener | 20 | Poison |
| Grand Master | Central | 4 | Decay Strengthener | 20 | Decay / Poison Strengthener |
| Grand Master | Central | 4 | Evil Spirit Streng | 20 | Evil Spirit |
| Grand Master | Central | 4 | Magic Mastery | 20 | Evil Spirit Streng |
| Grand Master | Central | 5 | Hellfire Strengthener | 20 | Hellfire |
| Grand Master | Central | 5 | Ice Strengthener | 20 | Ice |
| Grand Master | Derecha | 2 | One-handed Staff Stren | 20 | — |
| Grand Master | Derecha | 2 | Shield Strengthener | 20 | — |
| Grand Master | Derecha | 2 | Two-handed Staff Stren | 20 | — |
| Grand Master | Derecha | 3 | One-handed Staff Mast | 10 | One-handed Staff Stren |
| Grand Master | Derecha | 3 | Shield Mastery | 20 | Shield Strengthener |
| Grand Master | Derecha | 3 | Two-handed Staff Mast | 20 | Two-handed Staff Stren |
| Grand Master | Derecha | 4 | Soul Barrier Strength | 20 | Soul Barrier |
| Grand Master | Derecha | 5 | Minimum Wizardry Inc | 20 | — |
| Grand Master | Derecha | 5 | Soul Barrier Proficie | 20 | Soul Barrier Strength |
| High Elf | Central | 2 | Heal Strengthener | 20 | Heal |
| High Elf | Central | 2 | Summoned Monster Str (1) | 20 | Summon Goblin |
| High Elf | Central | 2 | Triple Shot Strengthener | 20 | Triple Shot |
| High Elf | Central | 3 | Defense Increase Str | 20 | Greater Defense |
| High Elf | Central | 3 | Penetration Strengthener | 20 | Penetration |
| High Elf | Central | 3 | Summoned Monster Str (2) | 20 | Summon Goblin |
| High Elf | Central | 3 | Triple Shot Mastery | 10 | Triple Shot Strengthener |
| High Elf | Central | 4 | Attack Increase Str | 20 | Greater Damage |
| High Elf | Central | 4 | Weapon Mastery | 20 | — |
| High Elf | Central | 5 | Attack Increase Mastery | 20 | Attack Increase Str |
| High Elf | Central | 5 | Defense Increase Mastery | 20 | Defense Increase Str |
| High Elf | Central | 5 | Ice Arrow Strengthener | 20 | Ice Arrow |
| High Elf | Derecha | 2 | Bow Strengthener | 20 | — |
| High Elf | Derecha | 2 | Crossbow Strengthener | 20 | — |
| High Elf | Derecha | 2 | Shield Strengthener | 20 | — |
| High Elf | Derecha | 3 | Bow Mastery | 10 | Bow Strengthener |
| High Elf | Derecha | 3 | Crossbow Mastery | 20 | Crossbow Strengthener |
| High Elf | Derecha | 3 | Shield Mastery | 20 | Shield Strengthener |
| High Elf | Derecha | 5 | Infinity Arrow Str | 20 | Infinity Arrow |
| High Elf | Derecha | 5 | Minimum Att Power Inc | 20 | — |
| Dimension Master | Central | 2 | Fire Tome Strengthener | 20 | — |
| Dimension Master | Central | 2 | Lightning Tome Stren | 20 | — |
| Dimension Master | Central | 2 | Wind Tome Strengthener | 20 | — |
| Dimension Master | Central | 3 | Fire Tome Mastery | 20 | Fire Tome Strengthener |
| Dimension Master | Central | 3 | Lightning Tome Mastery | 20 | Lightning Tome Stren |
| Dimension Master | Central | 3 | Sleep Strengthener | 20 | Sleep |
| Dimension Master | Central | 3 | Wind Tome Mastery | 20 | Wind Tome Strengthener |
| Dimension Master | Central | 4 | Chain Lightning Str | 20 | Chain Lightning |
| Dimension Master | Central | 4 | Lightning Shock Str | 20 | Lightning Shock |
| Dimension Master | Central | 5 | Drain Life Strengthener | 20 | Drain Life |
| Dimension Master | Central | 5 | Magic Mastery | 20 | — |
| Dimension Master | Derecha | 2 | Other World Tome Streng | 20 | — |
| Dimension Master | Derecha | 2 | Stick Strengthener | 20 | — |
| Dimension Master | Derecha | 3 | Other World Tome Mastery | 10 | Other World Tome Streng |
| Dimension Master | Derecha | 3 | Stick Mastery | 20 | Stick Strengthener |
| Dimension Master | Derecha | 4 | Berserker Strengthener | 20 | Berserker |
| Dimension Master | Derecha | 5 | Berserker Proficiency | 20 | Berserker Strengthener |
| Dimension Master | Derecha | 5 | Minimum Wiz/Curse Inc | 20 | — |
| Duel Master | Central | 2 | Cyclone Strengthener | 20 | Cyclone |
| Duel Master | Central | 2 | Lightning Strengthener | 20 | Lightning |
| Duel Master | Central | 2 | Power Slash Streng | 20 | Power Slash |
| Duel Master | Central | 2 | Twisting Slash Stren | 20 | Twisting Slash |
| Duel Master | Central | 3 | Blast Strengthener | 20 | Cometfall / Lightning Strengthener |
| Duel Master | Central | 3 | Flame Strengthener | 20 | Flame |
| Duel Master | Central | 3 | Weapon Mastery | 20 | Twisting Slash Stren / Power Slash Streng |
| Duel Master | Central | 4 | Evil Spirit Strengthen | 20 | Evil Spirit |
| Duel Master | Central | 4 | Inferno Strengthener | 20 | Inferno / Flame Strengthener |
| Duel Master | Central | 4 | Magic Mastery | 20 | Evil Spirit Strengthen |
| Duel Master | Central | 5 | Blood Attack Strengthen | 20 | Fire Slash |
| Duel Master | Central | 5 | Ice Strengthener | 20 | Ice |
| Lord Emperor | Central | 2 | Dark Horse Streng (1) | 20 | — |
| Lord Emperor | Central | 2 | Fire Burst Streng | 20 | Fire Burst |
| Lord Emperor | Central | 2 | Force Wave Streng | 20 | Force |
| Lord Emperor | Central | 3 | Critical DMG Inc PowUp | 20 | Increase Critical Damage |
| Lord Emperor | Central | 3 | Earthshake Streng | 20 | Earthshake / Dark Horse Streng (1) |
| Lord Emperor | Central | 3 | Weapon Mastery | 20 | — |
| Lord Emperor | Central | 4 | Crit DMG Inc PowUp (2) | 20 | Critical DMG Inc PowUp |
| Lord Emperor | Central | 4 | Earthshake Mastery | 20 | Earthshake Streng |
| Lord Emperor | Central | 4 | Fire Burst Mastery | 20 | Fire Burst Streng |
| Lord Emperor | Central | 5 | Crit DMG Inc PowUp (3) | 20 | Crit DMG Inc PowUp (2) |
| Lord Emperor | Central | 5 | Fire Scream Stren | 20 | Fire Scream |
| Lord Emperor | Derecha | 2 | Dark Spirit Str | 20 | — |
| Lord Emperor | Derecha | 2 | Scepter Strengthener | 20 | — |
| Lord Emperor | Derecha | 2 | Shield Strengthener | 20 | — |
| Lord Emperor | Derecha | 2 | Use Scepter : Pet Str | 20 | — |
| Lord Emperor | Derecha | 3 | Command Attack Inc | 20 | — |
| Lord Emperor | Derecha | 3 | Dark Spirit Str (2) | 20 | Dark Spirit Str |
| Lord Emperor | Derecha | 3 | Scepter Mastery | 20 | Scepter Strengthener |
| Lord Emperor | Derecha | 3 | Shield Mastery | 20 | Shield Strengthener |
| Lord Emperor | Derecha | 5 | Dark Spirit Str (3) | 20 | Dark Spirit Str (2) |
| Lord Emperor | Derecha | 5 | Pet Durability Str | 20 | — |
| Fist Master | Izquierda (común) | 1 | Durability Reduction (1) | 20 | — |
| Fist Master | Izquierda (común) | 1 | Increase PvP Defense Rate | 20 | — |
| Fist Master | Izquierda (común) | 2 | Increase Mana Recovery Rate | 20 | — |
| Fist Master | Izquierda (común) | 2 | Increase Maximum SD | 20 | — |
| Fist Master | Izquierda (común) | 2 | Increase Poison Resistance | 20 | — |
| Fist Master | Izquierda (común) | 3 | Durability Reduction (2) | 20 | Durability Reduction (1) |
| Fist Master | Izquierda (común) | 3 | Increase HP Recovery Rate | 20 | Increase Mana Recovery Rate |
| Fist Master | Izquierda (común) | 3 | Increase Lightning Resistance | 20 | Increase Poison Resistance |
| Fist Master | Izquierda (común) | 3 | Increase SD Recovery Rate | 20 | Increase Maximum SD |
| Fist Master | Izquierda (común) | 4 | Increase Ice Resistance | 20 | Increase Lightning Resistance |
| Fist Master | Izquierda (común) | 4 | Increases AG Recovery Rate | 20 | Increase HP Recovery Rate |
| Fist Master | Izquierda (común) | 4 | Increases Defense | 20 | — |
| Fist Master | Izquierda (común) | 5 | Durability Reduction(3) | 20 | Durability Reduction (2) |
| Fist Master | Izquierda (común) | 5 | Increase Defense Success Rate | 20 | Increases Defense |
| Fist Master | Central | 1 | Increase Attack Success Rate | 20 | — |
| Fist Master | Central | 2 | Beast Uppercut Strengthener | 20 | — |
| Fist Master | Central | 2 | Killing Blow Strengthener | 20 | — |
| Fist Master | Central | 3 | Beast Uppercut Mastery | 20 | Beast Uppercut Strengthener |
| Fist Master | Central | 3 | Killing Blow Mastery | 20 | Killing Blow Strengthener |
| Fist Master | Central | 4 | Increase Maximum HP | 20 | — |
| Fist Master | Central | 4 | Weapon Mastery | 20 | — |
| Fist Master | Central | 5 | Chain Drive Strengthener | 20 | Chain Drive |
| Fist Master | Central | 5 | Dark Side Strengthener | 20 | Dark Side |
| Fist Master | Central | 5 | Dragon Roar Strengthener | 20 | Dragon Roar |
| Fist Master | Central | 5 | Increase Maximum Mana | 20 | Increase Maximum HP |
| Fist Master | Derecha | 1 | Increase PvP Attack Rate | 20 | — |
| Fist Master | Derecha | 2 | Def SuccessRate IncPowUp | 20 | Increase Block |
| Fist Master | Derecha | 2 | Equipped Weapon Strengthener | 20 | — |
| Fist Master | Derecha | 3 | DefSuccessRate IncMastery | 20 | Def SuccessRate IncPowUp |
| Fist Master | Derecha | 3 | Equipped Weapon Mastery | 20 | Equipped Weapon Strengthener |
| Fist Master | Derecha | 4 | Decrease Mana | 20 | — |
| Fist Master | Derecha | 4 | Recover HP from Monster Kills | 20 | — |
| Fist Master | Derecha | 4 | Recover SD from Monster Kills | 20 | — |
| Fist Master | Derecha | 4 | Stamina Increase Strengthener | 20 | Increase Health |
| Fist Master | Derecha | 5 | Increase Minimum Attack Power | 20 | — |
| Fist Master | Derecha | 5 | Recover Mana Monster Kills | 20 | Recover HP from Monster Kills |

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
