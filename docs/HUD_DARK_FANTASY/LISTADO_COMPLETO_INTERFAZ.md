# Listado completo de la interfaz — qué existe, qué está limpio, qué falta diseñar

Generado 2026-10-09. Enumera **todas** las clases de ventana NewUI del cliente (carpeta `src/source/UI/NewUI`), agrupadas por categoría. "Limpio" = sin imagen de fondo propia, listo para recibir el diseño nuevo. "Pendiente" = todavía muestra el arte original de Webzen (gris piedra tallada) y no se ha tocado.

## Hecho esta sesión (transparente, sin imagen de fondo)

| Ventana | Archivo | Notas |
|---|---|---|
| Inventario (marco) | `Inventory/NewUIMyInventory.cpp` | slot dedicado `IMAGE_INVENTORY_FRAME_BG` |
| Artifact / Pentagram | `Inventory/NewUIMyInventory.cpp` | slot dedicado `IMAGE_ARTIFACT_PANEL_BG` |
| Panel de Personaje (stats) | `Character/NewUICharacterInfoWindow.cpp` | slot dedicado `IMAGE_CHAINFO_PANEL_BG` |
| Barra inferior (HP/MP/EXP/skills) | `HUD/NewUIMainFrameWindow.cpp` | `IMAGE_MENU_1` sin cargar, 6 llamadas de dibujo comentadas |
| Message Box genérico (Error, confirmaciones) | `Dialogs/NewUICommonMessageBox.cpp` | 2 funciones, ambas limpias |
| Menú rápido (tecla U) | `Dialogs/NewUIWindowMenu.h` | comparte fondo con Message Box, ya limpio de rebote |
| ~13 variantes de mensaje (recompensas, confirmaciones, etc.) | `Dialogs/NewUICustomMessageBox.cpp` | 117 líneas de `RenderImage(...MSGBOX...)` comentadas |
| Cursed Temple (entrar/resultado) | `Events/NewUICursedTempleEnter.cpp`, `NewUICursedTempleResult.cpp` | mismo patrón, limpio |
| Barra de Skills (slots de habilidad) | `HUD/NewUIMainFrameWindow.cpp` (`RenderHudSkillFrameV6`) | **nunca tuvo textura** — ya es solo color plano por diseño original, no requiere cambio |

## Revisado pero NO tocado aún (mismo patrón MSGBOX, otro formato de línea — el script no los detectó)

| Ventana | Archivo |
|---|---|
| Diálogo de reconexión | `Dialogs/ReconnectDialog.cpp` |
| Lucky Item (Caja de la suerte) | `Inventory/NewUILuckyItemWnd.cpp` |
| Compra en tienda NPC | `Inventory/NewUIPurchaseShopInventory.cpp` |

## Pendiente — nunca tocado, sigue con el arte original de Webzen

### Inventario / objetos
- Baúl (`NewUIStorageInventory`, `NewUIStorageInventoryExt`)
- Comercio / Trade (`NewUITrade`)
- Mi tienda personal (`NewUIMyShopInventory`)
- Chaos Machine / Mix (`NewUIMixInventory`) — **no tocar la lógica de recetas, solo el arte**
- Ampliación de inventario (`NewUIInventoryExtension`)
- Mercado unificado (`NewUIUnitedMarketPlaceWindow`)
- Tooltips de ítem (`NewUIItemExplanationWindow`, `NewUISetItemExplanation`, `NewUIItemEnduranceInfo`)

### NPCs
- Tienda NPC (`NewUINPCShop`)
- Diálogo de NPC (`NewUINPCDialogue`)
- Guardián del Imperio (`NewUIEmpireGuardianNPC/Timer`)
- Portero / Gateman (`NewUIGatemanWindow`)

### Quests
- Info de mi quest (`NewUIMyQuestInfoWindow`)
- Quest de NPC (`NewUINPCQuest`)
- Progreso de quest (`NewUIQuestProgress`, `NewUIQuestProgressByEtc`)

### Party / Guild / Social
- Lista de amigos (`NewUIFriendWindow`) — la ventana "Mi amigo" que mostraste, **ojo: usa el sistema LEGACY `UIWindows.cpp`, no NewUI** — requiere tratamiento aparte
- Info de party (`NewUIPartyInfoWindow`)
- Lista de party (`NewUIPartyListWindow`)

### Combate / Eventos
- Castle Siege (`NewUICastleWindow`, `NewUISiegeWar*` x4)
- Duelo (`NewUIDuelWindow`, `NewUIDuelWatch*` x3)
- Guardia (`NewUIGuardWindow`)
- Blood Castle, Devil Square, Chaos Castle, Doppelganger, Crywolf, Kanturu, Battle Soccer, Gold Bowman (x2), Exchange Lucky Coin, Registration Lucky Coin, Gate Switch, Catapult — todos en `Events/`

### HUD adicional
- Ventana de buffs (`NewUIBuffWindow`)
- Log de chat (`NewUIChatLogWindow`)
- Ranking Gens (`NewUIGensRanking`)
- Minimapa (`NewUIMiniMap`)
- Comando rápido / movimiento (`NewUIQuickCommandWindow`, `NewUIMoveCommandWindow`)
- Master Level (`NewUIMasterLevel`)

### Otros
- Opciones (`NewUIOptionWindow`)
- Ayuda (`NewUIHelpWindow`)
- Comandos de chat (`NewUIChatCommandWindow`)
- Widgets base (scrollbar, combobox, textbox) — probablemente no necesitan arte propio, son controles genéricos

### Fuera de NewUI (sistemas aparte, requieren investigación propia antes de tocar)
- **Pantalla de login** (selección de servidor, cuenta/contraseña) — no usa `RenderImage`/`LoadBitmap` del mismo modo, pendiente de ubicar su sistema real
- **Selección de personaje**
- **Ventana de Amigos** (`UIWindows.cpp`, sistema legacy distinto a NewUI)
- Mapa completo (tecla M, distinto del minimapa)

## Siguiente paso sugerido

Con todo lo de arriba limpio, el orden razonable para ir metiendo diseño nuevo (sin romper lo ya limpio):
1. Confirmar que esta tanda de limpieza se ve bien en el juego.
2. Diseñar y aplicar el arte nuevo a las 5 piezas ya limpias (Inventario, Artifact, Personaje, HUD inferior, Message Box genérico) — cubre la mayoría de lo que se ve todo el tiempo.
3. Baúl + Comercio + Tienda NPC (uso frecuente).
4. Quests + Party/Guild.
5. Eventos especiales (Castle Siege, Blood Castle, etc. — uso ocasional, menor prioridad visual).
6. Login / selección de personaje (sistema aparte, requiere investigación propia).
