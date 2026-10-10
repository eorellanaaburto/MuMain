# V7 AEGIS — Plan de implementación en el cliente real Season 8

## Objetivo de este entregable

V7 es una propuesta visual (PNG + SVG) montada sobre una captura real.
No es un parche C++ ni un paquete OZJ ya integrado. Las vistas son para validar
la composición ANTES de sustituir de nuevo el HUD del juego.

## Por qué V6 se ve mal

1. La barra panorámica se dibuja desde Y=384 en las coordenadas lógicas del cliente,
   pero elementos interactivos originales y orbes siguen cerca de la franja inferior.
2. Títulos, números, gauge e iconos se componen por distintas rutas de dibujo.
3. El atlas panorámico y los marcos de cada habilidad no comparten una única geometría.
4. Se cambió la textura sin actualizar simultáneamente layout, hitbox, estados y escalado.

## Código disponible y puntos reales de intervención

Ruta de proyecto: `C:\Users\Usuario\Documents\Codex\2026-09-30\et\work\MuMain`

Archivo verificado en el paquete V6:
`src/source/UI/NewUI/HUD/NewUIMainFrameWindow.cpp`

- `CNewUIMainFrameWindow::LoadImages()` carga los tres menús `newui_menu01/02/03`.
- `CNewUIMainFrameWindow` dibuja barras HP, MP, SD, AG y EXP mediante funciones propias.
- `CNewUISkillList::Render()` dibuja casillas activas y selección de habilidades.
- `CNewUISkillList::UpdateMouseEvent()` procesa acciones del ratón.
- `CNewUISkillList::RenderCurrentSkillAndHotSkillList()` procesa habilidades y atajos.

El implementador debe definir un solo `HudLayout` en el espacio lógico de referencia,
y usar sus mismas coordenadas en dibujo, tooltip y eventos del mouse.

## Criterios de implementación

1. Mantener intacto el motor de habilidades: ID Master, paquetes, mapeo, teclas,
   cooldowns, selección y ejecución (incluidas las reparaciones de Cyclone Strengthener).
2. Barra CONTINUA, sin repetir un atlas por cada tramo con dimensiones incompatibles.
3. Diez habilidades en una fila, con dimensiones consistentes y sin dibujar marcos
   de otra interfaz por detrás. Las ilustraciones finales deben ser las habilidades
   reales del cliente, no los símbolos SVG de esta vista previa.
4. Redibujar valores actuales de HP/MP/SD/AG/EXP; los números presentes en la
   vista previa son ejemplos y NO deben fijarse en código.
5. Orbes dinámicos: recorte/llenado proporcional con textura compatible OZJ/OZT.
6. Bloque `LVL / RESET / PTS` con datos reales. Color PTS #FF9C24.
7. Escalar a 1280x720, 1360x768 y 1920x1080 verificando hitboxes/escala.
8. Artifact e inventario: layout independiente; no tapar el mundo ni las barras;
   comprobar que slots y clics mantengan la misma geometría.
9. Respaldar C++ y OZJ; instalar únicamente en `Mu-S8 COMPILADO PRUEBA`.
10. Compilar Release con el CMake ya configurado; validar arranque sin LoadBitmap Failed.

## Archivos visuales incluidos

- PREVIA/HUD_V7_PREVIA.png
- PREVIA/HUD_V7_INVENTARIO_ARTIFACT.png
- PREVIA/HUD_V7_CAPA_TRANSPARENTE.png (composición visual; NO es textura .OZJ)
- FUENTES/*.svg (vectores originales editables)
- VISTA_PREVIA_V7.html

## Lo que NO se debe hacer

- No renombrar PNG/JPG/SVG como .OZJ.
- No copiar la maqueta HTML a `Data/Interface`.
- No instalar `Main.exe` sobre el cliente funcional.
- No cambiar solo Y del atlas sin cambiar geometría real de los controles.
- No prometer que las habilidades o Artifact quedan corregidos solo por el diseño.
