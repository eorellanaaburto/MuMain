# MU S8 — Propuesta HUD V7 Aegis

Este ZIP incluye un rediseño VISUAL REALIZADO SOBRE UNA CAPTURA DEL CLIENTE, no una actualización del juego.

Objetivos de V7:
- Barra inferior CONTINUA, compacta y proporcional: sin tramos cortados ni título gigante sobre controles.
- Orbes HP/MP claros e integrados con las estadísticas.
- 10 habilidades en fila con marcos coherentes, sin diamantes decorativos ni superposición de botones.
- EXP fina y bloques SD/AG legibles.
- Inventario/Artifact en paneles independientes y alineados, con separación visible.
- Respetar el código C++ de habilidades y los paquetes originales del cliente.

Archivo principal: VISTA_PREVIA_V7.html. Vista previa PNG: PREVIA/HUD_V7_PREVIA.png.
Imagen PNG de paneles: PREVIA/HUD_V7_INVENTARIO_ARTIFACT.png.
Fuentes editables SVG en FUENTES/.

IMPORTANTE: No copiar los SVG ni PNG a Data\Interface ni renombrarlos .OZJ.
V7 es un diseño de revisión que debe implementarse luego en el código C++ de MuMain,
resolviendo también geometría, escalado y áreas de clic de los controles.

Referencias consultadas:
https://github.com/xulek/MuOnlineConsoleClient  (organización de información e indicadores)
https://github.com/bernatvadell/muonline (sistema escalable de UI)
https://www.behance.net/search/projects/mu%20online%20launcher?locale=es (inspiración de lenguaje gráfico fantasy)

No se han copiado iconos, texturas ni código de terceros. El diseño es original.
