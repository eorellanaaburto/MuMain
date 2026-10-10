# Implementación Dark Fantasy — contrato técnico

## Principio de arquitectura

La captura real de la versión de pruebas y el código V6 muestran que una parte operativa del HUD se renderiza a través de funciones C++ en `src/source/UI/NewUI/HUD/NewUIMainFrameWindow.cpp` (incluyendo `CNewUISkillList`) que cargan recursos *legacy* mediante rutas `Interface\newui_menu01.jpg`, `Interface\newui_menu02.jpg` y `Interface\partCharge1\newui_menu03.jpg`. **El cargador busca los correspondientes `.OZJ`**, no los `.jpg` que aparecen en el código. Las texturas GFx `MainFrame.ozg` y `InventoryFrame.ozg` son recursos adicionales y NO deben darse por propietarios de toda la UI actual sin verificar cómo se cargan las ventanas. El diseño debe migrarse por capas y validar cada ventana operativa.

## Archivos C++ base confirmados

1. `src/source/UI/NewUI/HUD/NewUIMainFrameWindow.cpp`: `LoadImages()`, dibujo del HUD, orbes, HUD dinámico y clase `CNewUISkillList`, manejo de ratón y teclado, render de slots, iconos y cooldown.
2. `src/source/UI/NewUI/HUD/NewUIMainFrameWindow.h`: interfaz y constantes relativas al HUD.
3. Localizar en el proyecto la fuente de ventana de estadísticas (Lv/R/Pts, especialmente color `#FF9C24`), de inventario expandido y de Artifact. **No se ha confirmado su nombre/ruta exactos:** no reemplazar por patrones de coincidencia vagos.
4. Para habilidades, mantener intactos `SkillCast.cpp`, `SkillManager.cpp`, y demás archivos modificados durante reparaciones; no restaurar todo el repositorio a una versión vieja.

## Recursos de producción que deben construirse (no están hechos)

- `Data/Interface/newui_menu01.OZJ` — segmento izquierdo del HUD; ancho/alto compatibles con el muestreo de coordenadas C++ final.
- `Data/Interface/newui_menu02.OZJ` — segmento central.
- `Data/Interface/partCharge1/newui_menu03.OZJ` — segmento derecho.
- Atlas o sprite adicional para orbes HP/MP con fondos y bordes individuales; el cargador y código de dibujo deben reconocerlo antes de instalarlo.
- Marcos de diez slots, estado seleccionado/hover/deshabilitado, indicadores de cooldown; conservar iconos originales.
- Barra EXP, AG, SD con fondos y rellenos separados; números correctamente anclados.
- Panel Lv/R/Pts naranja.
- Inventario/Artifact: texturas nuevas **solo luego de identificar las fuentes de render actuales**, adaptando coordenadas, clipping, Z-order y hitboxes.

## Elementos pendientes de implementar en C++

1. Un HUD continuo en el espacio lógico del motor (referencia observada: 640×480) que escale a resoluciones físicas 1024×768, 1366×768 y 1920×1080; NO pegar la imagen 1672×941 como textura.
2. Cálculo de posición a partir de anclajes y bounding boxes, y actualización paralela de hitboxes de botones.
3. Orbes nuevos, barras dinámicas con máscaras correctas, números de HP/MP/AG/SD sin solapamiento y con datos de juego reales.
4. Barra de 10 slots con estados y mapeos originales de teclas, ratón, animaciones, cooldowns y packets intactos.
5. Estado compacto superior izquierdo y `Pts` en `#FF9C24`.
6. Ventanas inventario + Artifact con paneles independientes y captura de ratón correcta; evitar abrir artefactos sobre inventario.

## Pruebas obligatorias

- Arranque sin `LoadBitmap Failed`.
- 1024×768, 1366×768, 1920×1080 y escala Windows elevada.
- HP/MP/SD/AG actualizando, EXP sin desbordes.
- Skills activas y con cooldown, Cyclone Strengthener y demás arreglos anteriores.
- Abrir, mover y cerrar inventario y Artifact; sin solapamientos o clics fantasma.
- Puntos, resets, trade, Gaion, Monster Wings: control de regresión.

## Regla de despliegue

Compilar primero en una copia de pruebas. Copiar a cliente final **solo después** de pruebas funcionales; nunca instalar de forma silenciosa al original.
