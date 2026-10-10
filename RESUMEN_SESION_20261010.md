# Resumen de sesión — MU Online Season 8 / CT122 — 2026-10-10

Este documento **reemplaza y actualiza** a `/root/RESUMEN_SESION_20261009.md` (del día anterior). Léelo primero si quieres contexto histórico, pero la información de ESTE archivo es la vigente — varias cosas descritas como "confirmadas" en el documento del 9 resultaron estar mal, según lo descubierto hoy.

## Estado actual del servidor (verificado estable)

- Imagen Docker activa: **`mu-openmu-local:pentagram-plugin-stage1-20261006`** (compilada el 6 de octubre, ANTES de cualquier cambio de esta sesión del 9-10 de octubre).
- `docker-compose.yml` restaurado a: `/opt/mu-online/docker-compose.pre-errtel-rates-20261009.yml` (ese es el contenido vigente ahora).
- Arranca limpio, sin errores, sin excepciones. Confirmado por el usuario que inventario, equipo, armas y habilidades funcionan normalmente.
- Base de datos: `config."GameConfiguration"."MaximumCharactersPerAccount" = 5` (ver más abajo por qué, sección "El bug real del límite de personajes").
- Plugin `PentagramInventoryListPlugIn` (GUID `a4af9115-24bb-4830-a6cf-e0c8556b8b58`) con `IsActive = true` — correcto para esta imagen, NO tocar.
- Cuenta `meinmundy`: tiene 5 personajes (Meinmundy, DMundy, MCoscuro, Mlucha, MOscuro). El personaje de prueba `MGTEST` fue borrado hoy (ver abajo) y el usuario pidió luego "reactivarlo" — no se pudo restaurar el dato exacto (no había backup previo a borrarlo), quedó pendiente que el usuario lo recree manualmente en el juego si quiere, ahora que el límite real de personajes está resuelto en teoría (aunque no en esta imagen — ver siguiente sección).
- Cuentas `T4rs` y `dvR`: tienen 6 personajes reales cada una. **Sobre la imagen actualmente activa (`pentagram-plugin-stage1-20261006`), NO tienen el fix real del límite de 6 personajes** — si alguna de ellas intenta entrar, es muy probable que sufra el mismo freeze/desconexión que tuvo `meinmundy` hoy. No se les ha avisado ni tocado nada. Esto queda pendiente.

## El bug real del límite de personajes (encontrado y entendido hoy)

No es un parámetro cosmético: el paquete de lista de personajes (`CharacterListExtendedRef`, código servidor en `Network/Packets/ServerToClient/ServerToClientPacketsRef.cs`) usaba un campo de tamaño de **1 byte** (máximo 255). Con 5 personajes el paquete pesa 228 bytes (cabe). Con 6 personajes pesa 272 bytes — se desborda, el campo de tamaño se corrompe, el servidor no puede enviar el siguiente paquete y corta la conexión justo al pedir la lista de personajes. Esto fue la causa real del "pantalla negra / debo cerrar a la fuerza" que reportó el usuario.

**La buena noticia:** este fix YA estaba completamente implementado — tanto en el servidor (`ShowCharacterListExtendedPlugIn.cs` con lógica dinámica C1/C2 según tamaño) como en el cliente (`WSclient.cpp::ReceiveCharacterListExtended`, con un `HeaderShift` que detecta el formato C2 automáticamente) — en el árbol de código correcto: **`/opt/openmu-merge/src`**. El cliente que el usuario tiene instalado (`Mu-S8 COMPILADO PRUEBA`) YA incluye el lado cliente de este fix.

El problema es que la imagen actualmente activa en el servidor (`pentagram-plugin-stage1-20261006`) NO fue compilada desde `openmu-merge`, sino desde un árbol de código diferente y más viejo que nunca tuvo este fix. Por eso, aunque el cliente esté listo, el servidor sigue roto para cualquier cuenta con 6 personajes.

## Los DOS intentos fallidos de hoy (para que no se repitan)

### Intento 1: `mu-openmu-local:illusion-temple-final-20261009`
Compilado desde `/opt/openmu-pentagram-native-20261006` (un árbol de código DISTINTO a `openmu-merge` — no es una variante, es una base de OpenMU completamente diferente, con otro estilo de código, recursos de localización distintos, etc.). Se usó este árbol porque ahí ya estaba hecho el trabajo de Pentagrama (ver sección siguiente), pero:
- Al revisar el código fuente de `UpdateCharacterStatsExtendedPlugIn.cs` contra `ConnectionExtensions.cs::SendCharacterInformationExtendedAsync`, **el código fuente coincide perfectamente** (30 parámetros, mismo orden, mismo tipo). El bug NO está en el código — está en la compilación: esa carpeta tiene restos de compilaciones incrementales viejas (`bin/`, `obj/` mezclados, cosa que `openmu-merge` no tiene) y la imagen resultante quedó con una inconsistencia binaria interna entre ensamblados que deberían coincidir. Esto producía un `MissingMethodException` en vivo cada vez que un personaje entraba al mundo, dejando al jugador sin estadísticas/poder/equipo visible ("no tengo poder ni nada" fue el síntoma reportado).
- **Lección: no reutilizar `/opt/openmu-pentagram-native-20261006` para compilar nada más. Esa carpeta quedó con compilaciones corruptas mezcladas.**

### Intento 2: `openmu-merge:illusion-temple-real-20261010`
Compilado limpio desde el árbol correcto, `openmu-merge/src`, después de portar ahí los 8 archivos nuevos de Illusion Temple (ver lista abajo) + 2 ediciones. Compiló sin errores. PERO:
- `openmu-merge`'s `Player.cs` **nunca tuvo el sistema de Pentagrama** — no existe la propiedad `Player.PentagramStorage`. El plugin externo `PentagramNativePlugIn.dll` (que SÍ fue compilado contra el árbol viejo, donde esa propiedad existe) llama a esa propiedad inexistente y crashea (`MissingMethodException: Player.get_PentagramStorage()`) cada vez que el servidor intenta enviar el inventario al cliente — resultado: inventario vacío para todos los jugadores.
- Intenté la solución rápida (desactivar ese plugin para que caiga al envío de inventario normal) y funcionó para el inventario, pero obviamente el Pentagrama deja de funcionar del todo si se hace eso de forma permanente.

**Conclusión: ninguna de las dos imágenes de hoy quedó lista para producción. Ambas se revirtieron. El servidor volvió a la imagen del 6 de octubre (`pentagram-plugin-stage1-20261006`), que es la única confirmada estable ahora.**

## Los 8 archivos nuevos de Illusion Temple (implementación completa, funcionando a nivel de compilación, NO desplegados)

Ya están copiados en AMBOS árboles (`openmu-pentagram-native-20261006` y `openmu-merge/src`), con las 2 ediciones correspondientes aplicadas en ambos:

- `GameLogic/MiniGames/IllusionTemple/IllusionTempleContext.cs`
- `GameLogic/MiniGames/IIllusionTempleViewPlugIns.cs`
- `GameLogic/PlayerActions/MiniGames/EnterIllusionTempleAction.cs`
- `GameServer/RemoteView/MiniGames/IllusionTemple/ShowIllusionTempleStateViewPlugIn.cs`
- `GameServer/RemoteView/MiniGames/IllusionTemple/ShowIllusionTempleResultViewPlugIn.cs`
- `GameServer/RemoteView/MiniGames/IllusionTemple/ShowIllusionTempleSkillPointUpdateViewPlugIn.cs`
- `GameServer/MessageHandler/MiniGames/IllusionTempleEnterRequestHandlerPlugIn.cs`
- `GameServer/MessageHandler/MiniGames/IllusionTempleSkillRequestHandlerPlugIn.cs`

Ediciones aplicadas en ambos árboles:
- `GameLogic/MiniGames/MiniGameManager.cs` (agrega `using` + `case MiniGameType.IllusionTemple`)
- `GameServer/RemoteView/MiniGames/ShowMiniGameEnterResultViewPlugIn.cs` (agrega `case MiniGameType.IllusionTemple`)

Los datos de base de datos (6 filas de `MiniGameDefinition` + `ExitGate`, mapas 45-50) ya están insertados y son independientes de qué imagen corra — no se pierden con nada de esto.

## La ruta correcta para continuar (recomendada, no se ejecutó nada todavía)

**Paso 1 — Portar el núcleo de Pentagrama a `openmu-merge` UNA VEZ, de forma limpia.**
Buscar en `/opt/openmu-pentagram-native-20261006/src/GameLogic/Player.cs` (línea ~488: `public PentagramStorage? PentagramStorage => this._storages.PentagramStorage;`) y todo lo relacionado (la clase `PentagramStorage` en sí, los cambios en `Storages`/persistencia que la respaldan, y el plugin `/opt/pentagram-native-plugin-20261006/PentagramInventoryListPlugIn.cs`). Portar todo eso a `openmu-merge/src`, adaptando lo que haga falta (puede que openmu-merge tenga una estructura de `Storages` distinta — hay que revisar con cuidado, no copiar y pegar a ciegas).

**Paso 2 — Compilar desde `openmu-merge/src` con el Dockerfile de siempre:**
```
cd /opt/openmu-merge/src && docker build -f Startup/Dockerfile -t openmu-merge:<tag-nuevo> .
```
(Illusion Temple ya está portado ahí, no hace falta tocarlo de nuevo — ver sección anterior.)

**Paso 3 — Antes de desplegar en el contenedor real, probar con cuidado.** Si es posible, levantar un contenedor de prueba separado (otro `container_name`, otro puerto) apuntando a la misma base de datos de solo lectura o a una copia, y verificar en los logs que: (a) no hay `MissingMethodException` al entrar al mundo con un personaje real, (b) el inventario se envía completo, (c) el Pentagrama no crashea. Solo después de confirmar esto, actualizar `/opt/mu-online/docker-compose.yml` y hacer `docker compose up -d openmu-startup`.

**Paso 4 — Una vez estable con Pentagrama + Illusion Temple en `openmu-merge`:**
- Subir `MaximumCharactersPerAccount` a 6 otra vez.
- Avisar a las cuentas `T4rs` y `dvR` o verificar que puedan entrar sin problema (ya tienen 6 personajes reales).
- Recrear el personaje de prueba `MGTEST` en la cuenta `meinmundy` si el usuario todavía lo quiere.

**Nunca más usar `/opt/openmu-pentagram-native-20261006` para compilar nada — quedó con compilaciones corruptas mezcladas (ver "Intento 1" arriba). Si se necesita repasar código de ahí, solo leerlo como referencia, no compilarlo.**

## Pendientes heredados del día anterior (sin cambios, siguen abiertos)

- Kalima (7 "Gate to Kalima X"): sin coordenadas de entrada en ningún lado.
- Castle Gate1 (#277): mismo problema.
- Doppelganger: roster completo sin usar (Doppelganger Elf/Knight/Wizard/Magic Gladiator/Summoner + "Dark Lord", números 533-539).
- Pentagrama: tooltip con el bono real ELE ATK/DEF al pasar el mouse — necesita cambio de protocolo, no solo cliente.
- 8 carpetas de mapa del cliente sin registrar en el servidor (World 35, 43, 59, 73, 74, 75, 78, 82) — inertes, sin urgencia.
- Blood Castle ticket crafting "no deja combinar" — reportado por el usuario el día anterior, investigación empezada pero no concluida entonces (los datos de receta se veían correctos a primera vista). **ACTUALIZACIÓN:** Blood Castle Ticket se craftea en el mismo NPC Chaos Goblin (238) que estaba completamente roto por los 3 plugins faltantes (ver sección "Chaos Machine / Refine completamente rotos" más abajo) — es muy probable que este pendiente YA esté resuelto por ese mismo fix. Falta confirmar probándolo en el juego.
- Portal web `/inicio`: texto "48 recetas" ya escrito en el archivo pero el proceso Python (`mu-disconnect.py`, puerto 9996) no se ha reiniciado para que se vea.

## Accesos y convenciones (sin cambios)

- SSH: `ssh proxmox-laposada "pct exec 122 -- <comando>"` para correr cosas dentro del LXC 122.
- DB: `pct exec 122 -- docker exec -e PGPASSWORD='\\admin' mu-database psql -U postgres -d openmu -c "<SQL>"`.
- Para copiar archivos al LXC: `scp archivo proxmox-laposada:/tmp/` → `pct push 122 /tmp/archivo /tmp/archivo` → `pct exec 122 -- cp /tmp/archivo /destino/final`.
- `docker compose up -d openmu-startup` solo RECREA el contenedor si `docker-compose.yml` cambió de contenido; si solo cambiaste algo en la base de datos (como un `PlugInConfiguration.IsActive`), hace falta `docker restart mu-openmu` para que el proceso relea esa configuración.
- Backups de `docker-compose.yml` relevantes en `/opt/mu-online/`: `docker-compose.pre-errtel-rates-20261009.yml` (= la imagen buena actual), `docker-compose.pre-illusion-temple-20261010.yml`, `docker-compose.pre-plugin-mounts-fix-20261009.yml`, `docker-compose.pre-real-illusion-temple-20261010.yml` (los últimos tres quedaron obsoletos por los intentos fallidos de hoy, no usarlos).

## ADDENDUM — continuación 2026-10-10 (después de escrito lo de arriba)

### Corrección importante: el árbol de código real no es `openmu-merge`, es `/opt/openmu-v0910`
Al revisar 4 carpetas más que el usuario señaló (`/opt/openmu-v0910`, `/opt/openmu-pentagram-native-20261006`, `/opt/openmu-imperial`, `/opt/openmu-src`), se confirmó que **`/opt/openmu-v0910` es el árbol real que compiló la imagen actualmente activa** (`pentagram-plugin-stage1-20261006`):
- Tiene `PentagramStorage` en `Player.cs` (igual que `openmu-pentagram-native-20261006`, pero con una implementación distinta — son dos intentos separados del mismo feature).
- Tiene su propio `Startup/Dockerfile`, mismo patrón de build.
- Sin carpetas `bin/`/`obj/` sueltas (árbol limpio).
- `openmu-imperial` y `openmu-src` NO tienen Pentagrama en absoluto.

**Esto cambia la recomendación de la sección "La ruta correcta para continuar" de arriba**: en vez de portar Pentagrama a `openmu-merge` (que no lo tiene), probablemente conviene portar Illusion Temple + el fix de 6 personajes a **`openmu-v0910`** (que YA tiene Pentagrama funcionando). Falta confirmar si `openmu-v0910` ya tiene el fix de 6 personajes o no — no se verificó todavía.

### Bug nuevo encontrado y arreglado: Chaos Machine / Refine completamente rotos
Después de revertir el servidor a la imagen estable de la tarde, **se volvieron a romper 3 plugins** porque el `docker-compose.yml` restaurado (`pre-errtel-rates-20261009.yml`) es de ANTES de que se agregaran sus bind-mounts permanentes en una parte anterior de esta sesión:
- `ElementalCraftingPlugIn.dll`
- `S8MasterSkillCompatibilityPlugIn.dll`
- `MonsterWingsChaosMixPlugIn.dll` ← este es el que probablemente causaba que la Chaos Machine (NPC **Chaos Goblin**, número 238, en Noria — NO es "Charon", ese solo tiene la ventana pero cero recetas asociadas) y el Refine (NPC **Osbourne**, número 369, en Aida) no dejaran sacar/crear nada.

Se volvieron a agregar los 3 bind-mounts al `docker-compose.yml` actual, se reinició el contenedor, cargaron limpios (sin `FileNotFoundException` ni `MissingMethodException` — son compatibles con `openmu-v0910`). **CONFIRMADO por el usuario: la Chaos Machine ya funciona.** Queda pendiente confirmar el Refine (Osbourne, Aida) específicamente, aunque es muy probable que también se haya arreglado con el mismo fix.

### Pendiente nuevo: revisar TODOS los ranks del BK (Dark Knight), no solo 2
Se revisaron puntualmente "Blood Storm" (rank 9, skill 346) y "Swell Life" (rank 6, skill 363) a pedido del usuario — ambos con mapeo cliente→base correctamente cableado (`SkillManager.cpp::MasterSkillToBaseSkillIndex`, tabla `S8_RANK6_GLOBAL_MAPPING`: `case 346: return 344;` y `case 363: return 48;`) y con el patrón de base de datos esperado (TargetAttributeId vacío es normal en nodos "Strengthener"/"Mastery", no es bug).

**El usuario dice que en la práctica "nunca quedan bien" los ranks del BK** — contradice lo que se encontró solo para estos 2 skills. Esto sugiere que el problema real puede estar en OTROS ranks del BK que no se revisaron todavía (hay más: Cyclone, Slash, Twisting Slash, Death Stab, Rageful Blow, Lunge, Falling Slash, Chain Drive, Dragon Roar, Killing Blow, Beast Uppercut, etc. — cada uno con su propia cadena Strengthener/Mastery). Falta: (1) listar TODOS los skills del BK con su `MasterSkillDefinition` y confirmar que cada uno tiene su entrada correspondiente en la tabla de mapeo del cliente, y (2) probar en vivo con el cliente real cuál rank específico "no queda bien" y en qué sentido (¿no sube de nivel? ¿no aplica el bono? ¿se ve mal el número en la UI?) — el usuario no especificó el síntoma exacto todavía, hace falta preguntarle.

## CAMBIOS DEL CLIENTE (C++) — estado completo, 2026-10-10

### ⚠️ ALERTA CRÍTICA: nada de esto está comiteado a git
El repositorio del cliente (`C:\Users\Usuario\Documents\Codex\2026-09-30\et\work\MuMain`, rama `codex/ct124-acheron-npcs`) tiene **65 archivos modificados sin comitear** (6996 líneas agregadas, 1194 eliminadas) más **38 archivos nuevos sin agregar** (`git add`). Esto incluye TODO el trabajo de Pentagrama, Rank 6, Adniel, el fix de 6 personajes del lado cliente, etc. — de esta sesión y de sesiones anteriores (hay carpetas de respaldo fechadas desde el 6 y 7 de octubre). **Si este árbol de trabajo se pierde o se resetea sin comitear antes, se pierde TODO el código fuente de estos cambios.** No se hizo ningún commit porque no se pidió explícitamente — se recomienda hacerlo pronto (`git add -A && git commit`) para no arriesgar el trabajo.

Para ver el detalle exacto de cualquier archivo: `cd` al repo y correr `git -c safe.directory='*' diff -- <archivo>` (el repo tiene un problema de "dubious ownership" por permisos de Windows; ese flag lo evita sin tocar la config global).

### Compilado actual (Main.exe) — respaldado en el servidor
- **Hash SHA256**: `6D88B14145DEACBA74A90E3B940BAE1D278457817AE2612C431A60A3AD3E5DD8`
- **Tamaño**: 21,219,840 bytes (~20.2 MB)
- **Copia en el servidor**: `/root/mu-client-backups/Main-client-20261010.exe` (dentro del LXC 122) — verificado con el mismo hash tras la copia.
- **Log de sincronización**: se agregó una entrada nueva en `README_CAMBIOS.md` (raíz del repo del cliente) siguiendo el formato que ya existía ahí desde el 7 de octubre.
- Este es el `.exe` que ya tiene el usuario corriendo en `C:\Users\Usuario\Downloads\Mu-S8 COMPILADO PRUEBA\Main.exe` — incluye TODOS los fixes de cliente descritos abajo.

### Archivos con razón de cambio CONOCIDA (confirmados durante esta sesión y la anterior)

| Archivo | Qué cambia | Por qué |
|---|---|---|
| `GameLogic/Combat/SkillCast.cpp` (+242/-? líneas) | `SkillElf()`: revertido `LogicCurrentSkill == Spe_Num` a `currentSkill == Spe_Num` | `Spe_Num` se promueve a rango real (STR/Mastery) pero `LogicCurrentSkill` se mapeaba hacia abajo a base — nunca coincidían. Rompía Triple Shot/Penetration/Infinity Arrow de la Elfa en rango STR/Mastery. |
| `GameLogic/Quests/GM3rdChangeUp.cpp` | `CreateBalgasBarrackMonster()`: agregado `\|\| gMapManager.WorldActive == WD_6STADIUM` | El monstruo #409 "Balram (Trainee Soldier)" no tenía su modelo correcto en el mapa Arena, solo en Balgas Barrack/Refuge/Devil Square. |
| `UI/NewUI/Inventory/NewUIMyInventory.cpp` (+455/-? líneas, el más grande de los conocidos) | (1) Guardia `!IsPentagramPanelBlocked()` agregada a un `RenderItem3D` sin proteger. (2) `IsPentagramPanelBlocked()` extendida con `INTERFACE_INVENTORY_EXT`. Además: fix de log de Errtel, fix de "hit", fix de drop del Pentagrama (ver carpetas de respaldo `*.bak_errtel_logfix_20261006`, `*.bak_hitfix_20261006_*`, `*.bak_pentagram_dropfix_20261006`) | El ícono del Pentagrama se dibujaba encima de otras ventanas (tienda, baúl, combinación, Inventario Ampliado). |
| `Network/Server/WSclient.cpp` (+81/-? líneas) | `ReceiveCharacterListExtended()`: agregado `HeaderShift` que detecta si el paquete viene en formato C1 o C2 y ajusta los offsets. También logging `[PENTAGRAM-CLIENT]` en `ReceiveInventoryExtended()`. | Soporte para que la lista de personajes funcione con 6 personajes por cuenta (el bug real investigado hoy) — YA ESTÁ LISTO del lado cliente, solo falta que el servidor lo use (ver sección del límite de personajes arriba). |
| `GameLogic/Skills/SkillManager.cpp` (+142/-? líneas) | Tabla `S8_RANK6_GLOBAL_MAPPING` en `MasterSkillToBaseSkillIndex()`: ~35 entradas explícitas mapeando IDs de skill "rank" (Strengthener/Proficiency/Mastery) a su skill base, para that la lógica local del cliente (animaciones, buffs) reconozca el skill sin importar el rango. | Es el mecanismo central que hace que cualquier skill con master-rank (BK, Elfa, Mago, etc.) se comporte igual sin importar el rango — confirmado correcto para Blood Storm/Swell Life hoy, pero el usuario dice que otros ranks del BK "nunca quedan bien" (pendiente, ver arriba). |
| `Data/Items/Group12_Wing.json`, `Data/Items/Models/Group12_Wing.json` | Entradas nuevas para Wings of Chaos/Magic/Life (Group 12, #263-265) | Sin esto el cliente no tiene nombre/modelo para esos ítems — podía crashear al tenerlos en inventario. |
| `Data/Items/Group14_Potion.json`, `Data/Items/Models/Group14_Potion.json` | Entradas nuevas para los 4 materiales únicos (Hell Maine's Leather, Dark Phoenix Flame, Death Beam Knight Soul, Death King's Bone) y/o Cloak of Death | Mismo motivo — datos de cliente para ítems nuevos del servidor. |

### Archivos modificados SIN razón documentada en esta conversación (revisar con `git diff` antes de tocar)
Estos cambiaron (según `git status`/`git diff --stat`) pero no tengo contexto de sesión sobre el motivo exacto — probablemente de trabajo anterior sobre Adniel/Pentagrama/UI que no quedó visible en este resumen. **No asumir qué hacen sin revisar el diff real:**

- `UI/NewUI/Dialogs/NewUICustomMessageBox.cpp` / `.h` — **el cambio más grande de todos** (1630 líneas nuevas). Hay respaldos fechados `*.before-adniel-buttons-final-20261007-094741` y `*.before-adniel-level-rank-20261007-094524`, sugiriendo que es la ventana de diálogo personalizada de Adniel (botones, nivel/rango).
- `UI/NewUI/Inventory/NewUIMixInventory.cpp` / `.h` (+260 líneas) — probablemente la UI de combinación/mezcla, relacionada con Adniel también (hay respaldos `backup-adniel-mix-final-20261007-085626/`, `backup-adniel-crafting-20261007-085418/`).
- `UI/NewUI/Inventory/NewUIInventoryActionController.cpp` (+100 líneas) — hay respaldos `*.bak_pentagram_rightclick_20261006` y `*.bak_before_pentagram_rightclick_v2`, sugiere lógica de click-derecho para el Pentagrama.
- `UI/NewUI/Character/NewUICharacterInfoWindow.cpp` (+70 líneas)
- `UI/Legacy/UIMng.cpp` (+80 líneas)
- `Scenes/WebzenScene.cpp` (+84 líneas), `Scenes/LoadingScene.cpp`/`.h` (+45 líneas)
- `GameLogic/Combat/ClassAttack.cpp` (+36 líneas)
- `Engine/Object/ZzzCharacter.cpp`, `Engine/Object/ZzzInterface.cpp`
- `UI/NewUI/Inventory/NewUIItemMng.cpp` (-58 líneas, solo borra código)
- `UI/NewUI/Inventory/NewUITrade.cpp`, `NewUIInventoryCtrl.cpp`
- `Network/Server/SocketSystem.cpp`
- `Core/Globals/_TextureIndex.h`, `_define.h`, `_enum.h`, `_struct.h`
- `Data/GameConfig/GameConfigConstants.h`, `Data/GameData/ItemData/ItemDefinition.h`, `ItemEnumNames.cpp`
- `GameLogic/Items/InventoryUtils.h`
- `CMakeLists.txt`, `src/CMakeLists.txt`, `tests/ui/CMakeLists.txt`, `vcpkg.json`, `docs/item-data.md`
- 14 imágenes `.OZJ` en `Data/Interface/` (pantallas de intro/carga S8, menú) — cambios de arte, no de lógica.

### Archivos nuevos sin agregar a git (`??` en `git status`)
Incluyen auditorías de texto sobre skills (`MASTER_*_AUDIT.*`), un plan (`docs/superpowers/plans/2026-10-06-pentagram-artifact-stage1.md`), ~13 carpetas `backup-adniel-*`/`backup_master_*`/`backup_meteor394_*` (snapshots fechados del 6-7 de octubre de iteraciones sobre Adniel y el mapeo rank6), dos tests nuevos (`tests/ui/test_item_guardian_option.cpp`, `tests/ui/test_pentagram_slot.cpp`), y `src/source/UI/NewUI/Inventory/ItemPacketParser.cpp` (archivo nuevo, no solo modificado).
